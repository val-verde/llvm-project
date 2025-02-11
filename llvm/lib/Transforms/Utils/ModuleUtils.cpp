//===-- ModuleUtils.cpp - Functions to manipulate Modules -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This family of functions perform manipulations on Modules.
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/ModuleUtils.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/VectorUtils.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "moduleutils"

static void appendToGlobalArray(const char *Array, Module &M, Function *F,
                                int Priority, Constant *Data) {
  IRBuilder<> IRB(M.getContext());
  FunctionType *FnTy = FunctionType::get(IRB.getVoidTy(), false);

  // Get the current set of static global constructors and add the new ctor
  // to the list.
  SmallVector<Constant *, 16> CurrentCtors;
  StructType *EltTy = StructType::get(
      IRB.getInt32Ty(), PointerType::getUnqual(FnTy), IRB.getInt8PtrTy());
  if (GlobalVariable *GVCtor = M.getNamedGlobal(Array)) {
    if (Constant *Init = GVCtor->getInitializer()) {
      unsigned n = Init->getNumOperands();
      CurrentCtors.reserve(n + 1);
      for (unsigned i = 0; i != n; ++i)
        CurrentCtors.push_back(cast<Constant>(Init->getOperand(i)));
    }
    GVCtor->eraseFromParent();
  }

  // Build a 3 field global_ctor entry.  We don't take a comdat key.
  Constant *CSVals[3];
  CSVals[0] = IRB.getInt32(Priority);
  CSVals[1] = F;
  CSVals[2] = Data ? ConstantExpr::getPointerCast(Data, IRB.getInt8PtrTy())
                   : Constant::getNullValue(IRB.getInt8PtrTy());
  Constant *RuntimeCtorInit =
      ConstantStruct::get(EltTy, makeArrayRef(CSVals, EltTy->getNumElements()));

  CurrentCtors.push_back(RuntimeCtorInit);

  // Create a new initializer.
  ArrayType *AT = ArrayType::get(EltTy, CurrentCtors.size());
  Constant *NewInit = ConstantArray::get(AT, CurrentCtors);

  // Create the new global variable and replace all uses of
  // the old global variable with the new one.
  (void)new GlobalVariable(M, NewInit->getType(), false,
                           GlobalValue::AppendingLinkage, NewInit, Array);
}

void llvm::appendToGlobalCtors(Module &M, Function *F, int Priority, Constant *Data) {
  appendToGlobalArray("llvm.global_ctors", M, F, Priority, Data);
}

void llvm::appendToGlobalDtors(Module &M, Function *F, int Priority, Constant *Data) {
  appendToGlobalArray("llvm.global_dtors", M, F, Priority, Data);
}

static void appendToUsedList(Module &M, StringRef Name, ArrayRef<GlobalValue *> Values) {
  GlobalVariable *GV = M.getGlobalVariable(Name);
  SmallPtrSet<Constant *, 16> InitAsSet;
  SmallVector<Constant *, 16> Init;
  if (GV) {
    if (GV->hasInitializer()) {
      auto *CA = cast<ConstantArray>(GV->getInitializer());
      for (auto &Op : CA->operands()) {
        Constant *C = cast_or_null<Constant>(Op);
        if (InitAsSet.insert(C).second)
          Init.push_back(C);
      }
    }
    GV->eraseFromParent();
  }

  Type *Int8PtrTy = llvm::Type::getInt8PtrTy(M.getContext());
  for (auto *V : Values) {
    Constant *C = ConstantExpr::getPointerBitCastOrAddrSpaceCast(V, Int8PtrTy);
    if (InitAsSet.insert(C).second)
      Init.push_back(C);
  }

  if (Init.empty())
    return;

  ArrayType *ATy = ArrayType::get(Int8PtrTy, Init.size());
  GV = new llvm::GlobalVariable(M, ATy, false, GlobalValue::AppendingLinkage,
                                ConstantArray::get(ATy, Init), Name);
  GV->setSection("llvm.metadata");
}

void llvm::appendToUsed(Module &M, ArrayRef<GlobalValue *> Values) {
  appendToUsedList(M, "llvm.used", Values);
}

void llvm::appendToCompilerUsed(Module &M, ArrayRef<GlobalValue *> Values) {
  appendToUsedList(M, "llvm.compiler.used", Values);
}

static int compareNames(Constant *const *A, Constant *const *B) {
  Value *AStripped = (*A)->stripPointerCasts();
  Value *BStripped = (*B)->stripPointerCasts();
  return AStripped->getName().compare(BStripped->getName());
}

GlobalVariable *
llvm::setUsedInitializer(GlobalVariable &V,
                         const SmallPtrSetImpl<GlobalValue *> &Init) {
  if (Init.empty()) {
    V.eraseFromParent();
    return nullptr;
  }

  // Type of pointer to the array of pointers.
  PointerType *Int8PtrTy = Type::getInt8PtrTy(V.getContext(), 0);

  SmallVector<Constant *, 8> UsedArray;
  for (GlobalValue *GV : Init) {
    Constant *Cast =
        ConstantExpr::getPointerBitCastOrAddrSpaceCast(GV, Int8PtrTy);
    UsedArray.push_back(Cast);
  }
  // Sort to get deterministic order.
  array_pod_sort(UsedArray.begin(), UsedArray.end(), compareNames);
  ArrayType *ATy = ArrayType::get(Int8PtrTy, UsedArray.size());

  Module *M = V.getParent();
  V.removeFromParent();
  GlobalVariable *NV =
      new GlobalVariable(*M, ATy, false, GlobalValue::AppendingLinkage,
                         ConstantArray::get(ATy, UsedArray), "");
  NV->takeName(&V);
  NV->setSection("llvm.metadata");
  delete &V;
  return NV;
}

FunctionCallee
llvm::declareSanitizerInitFunction(Module &M, StringRef InitName,
                                   ArrayRef<Type *> InitArgTypes) {
  assert(!InitName.empty() && "Expected init function name");
  return M.getOrInsertFunction(
      InitName,
      FunctionType::get(Type::getVoidTy(M.getContext()), InitArgTypes, false),
      AttributeList());
}

Function *llvm::createSanitizerCtor(Module &M, StringRef CtorName) {
  Function *Ctor = Function::createWithDefaultAttr(
      FunctionType::get(Type::getVoidTy(M.getContext()), false),
      GlobalValue::InternalLinkage, 0, CtorName, &M);
  Ctor->addAttribute(AttributeList::FunctionIndex, Attribute::NoUnwind);
  BasicBlock *CtorBB = BasicBlock::Create(M.getContext(), "", Ctor);
  ReturnInst::Create(M.getContext(), CtorBB);
  // Ensure Ctor cannot be discarded, even if in a comdat.
  appendToUsed(M, {Ctor});
  return Ctor;
}

std::pair<Function *, FunctionCallee> llvm::createSanitizerCtorAndInitFunctions(
    Module &M, StringRef CtorName, StringRef InitName,
    ArrayRef<Type *> InitArgTypes, ArrayRef<Value *> InitArgs,
    StringRef VersionCheckName) {
  assert(!InitName.empty() && "Expected init function name");
  assert(InitArgs.size() == InitArgTypes.size() &&
         "Sanitizer's init function expects different number of arguments");
  FunctionCallee InitFunction =
      declareSanitizerInitFunction(M, InitName, InitArgTypes);
  Function *Ctor = createSanitizerCtor(M, CtorName);
  IRBuilder<> IRB(Ctor->getEntryBlock().getTerminator());
  IRB.CreateCall(InitFunction, InitArgs);
  if (!VersionCheckName.empty()) {
    FunctionCallee VersionCheckFunction = M.getOrInsertFunction(
        VersionCheckName, FunctionType::get(IRB.getVoidTy(), {}, false),
        AttributeList());
    IRB.CreateCall(VersionCheckFunction, {});
  }
  return std::make_pair(Ctor, InitFunction);
}

std::pair<Function *, FunctionCallee>
llvm::getOrCreateSanitizerCtorAndInitFunctions(
    Module &M, StringRef CtorName, StringRef InitName,
    ArrayRef<Type *> InitArgTypes, ArrayRef<Value *> InitArgs,
    function_ref<void(Function *, FunctionCallee)> FunctionsCreatedCallback,
    StringRef VersionCheckName) {
  assert(!CtorName.empty() && "Expected ctor function name");

  if (Function *Ctor = M.getFunction(CtorName))
    // FIXME: Sink this logic into the module, similar to the handling of
    // globals. This will make moving to a concurrent model much easier.
    if (Ctor->arg_size() == 0 ||
        Ctor->getReturnType() == Type::getVoidTy(M.getContext()))
      return {Ctor, declareSanitizerInitFunction(M, InitName, InitArgTypes)};

  Function *Ctor;
  FunctionCallee InitFunction;
  std::tie(Ctor, InitFunction) = llvm::createSanitizerCtorAndInitFunctions(
      M, CtorName, InitName, InitArgTypes, InitArgs, VersionCheckName);
  FunctionsCreatedCallback(Ctor, InitFunction);
  return std::make_pair(Ctor, InitFunction);
}

void llvm::filterDeadComdatFunctions(
    Module &M, SmallVectorImpl<Function *> &DeadComdatFunctions) {
  // Build a map from the comdat to the number of entries in that comdat we
  // think are dead. If this fully covers the comdat group, then the entire
  // group is dead. If we find another entry in the comdat group though, we'll
  // have to preserve the whole group.
  SmallDenseMap<Comdat *, int, 16> ComdatEntriesCovered;
  for (Function *F : DeadComdatFunctions) {
    Comdat *C = F->getComdat();
    assert(C && "Expected all input GVs to be in a comdat!");
    ComdatEntriesCovered[C] += 1;
  }

  auto CheckComdat = [&](Comdat &C) {
    auto CI = ComdatEntriesCovered.find(&C);
    if (CI == ComdatEntriesCovered.end())
      return;

    // If this could have been covered by a dead entry, just subtract one to
    // account for it.
    if (CI->second > 0) {
      CI->second -= 1;
      return;
    }

    // If we've already accounted for all the entries that were dead, the
    // entire comdat is alive so remove it from the map.
    ComdatEntriesCovered.erase(CI);
  };

  auto CheckAllComdats = [&] {
    for (Function &F : M.functions())
      if (Comdat *C = F.getComdat()) {
        CheckComdat(*C);
        if (ComdatEntriesCovered.empty())
          return;
      }
    for (GlobalVariable &GV : M.globals())
      if (Comdat *C = GV.getComdat()) {
        CheckComdat(*C);
        if (ComdatEntriesCovered.empty())
          return;
      }
    for (GlobalAlias &GA : M.aliases())
      if (Comdat *C = GA.getComdat()) {
        CheckComdat(*C);
        if (ComdatEntriesCovered.empty())
          return;
      }
  };
  CheckAllComdats();

  if (ComdatEntriesCovered.empty()) {
    DeadComdatFunctions.clear();
    return;
  }

  // Remove the entries that were not covering.
  erase_if(DeadComdatFunctions, [&](GlobalValue *GV) {
    return ComdatEntriesCovered.find(GV->getComdat()) ==
           ComdatEntriesCovered.end();
  });
}

std::string llvm::getUniqueModuleId(Module *M) {
  MD5 Md5;
  bool ExportsSymbols = false;
  auto AddGlobal = [&](GlobalValue &GV) {
    if (GV.isDeclaration() || GV.getName().startswith("llvm.") ||
        !GV.hasExternalLinkage() || GV.hasComdat())
      return;
    ExportsSymbols = true;
    Md5.update(GV.getName());
    Md5.update(ArrayRef<uint8_t>{0});
  };

  for (auto &F : *M)
    AddGlobal(F);
  for (auto &GV : M->globals())
    AddGlobal(GV);
  for (auto &GA : M->aliases())
    AddGlobal(GA);
  for (auto &IF : M->ifuncs())
    AddGlobal(IF);

  if (!ExportsSymbols)
    return "";

  MD5::MD5Result R;
  Md5.final(R);

  SmallString<32> Str;
  MD5::stringifyResult(R, Str);
  return ("." + Str).str();
}

void VFABI::setVectorVariantNames(
    CallInst *CI, const SmallVector<std::string, 8> &VariantMappings) {
  if (VariantMappings.empty())
    return;

  SmallString<256> Buffer;
  llvm::raw_svector_ostream Out(Buffer);
  for (const std::string &VariantMapping : VariantMappings)
    Out << VariantMapping << ",";
  // Get rid of the trailing ','.
  assert(!Buffer.str().empty() && "Must have at least one char.");
  Buffer.pop_back();

  Module *M = CI->getModule();
#ifndef NDEBUG
  for (const std::string &VariantMapping : VariantMappings) {
    LLVM_DEBUG(dbgs() << "VFABI: adding mapping '" << VariantMapping << "'\n");
    Optional<VFInfo> VI = VFABI::tryDemangleForVFABI(VariantMapping, *M);
    assert(VI.hasValue() && "Cannot add an invalid VFABI name.");
    assert(M->getNamedValue(VI.getValue().VectorName) &&
           "Cannot add variant to attribute: "
           "vector function declaration is missing.");
  }
#endif
  CI->addAttribute(
      AttributeList::FunctionIndex,
      Attribute::get(M->getContext(), MappingsAttrName, Buffer.str()));
}
