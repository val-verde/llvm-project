add_llvm_library(MLIRTargetLLVMIRModuleTranslation
  LLVMIR/ModuleTranslation.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Target/LLVMIR
  DEPENDS
  intrinsics_gen
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTargetLLVMIRModuleTranslation PUBLIC LLVM)
else ()
target_link_libraries(MLIRTargetLLVMIRModuleTranslation
  MLIRLLVMIR LLVMCore LLVMIRReader LLVMSupport LLVMTransformUtils
  MLIRTranslation)
endif ()
add_llvm_library(MLIRTargetLLVMIR
  LLVMIR/ConvertFromLLVMIR.cpp
  LLVMIR/ConvertToLLVMIR.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Target/LLVMIR
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTargetLLVMIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRTargetLLVMIR MLIRTargetLLVMIRModuleTranslation)
endif ()
add_llvm_library(MLIRTargetNVVMIR
  LLVMIR/ConvertToNVVMIR.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Target/LLVMIR
  DEPENDS
  intrinsics_gen
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTargetNVVMIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRTargetNVVMIR
  MLIRGPU
  MLIRIR
  MLIRLLVMIR
  MLIRNVVMIR
  MLIRTargetLLVMIRModuleTranslation
  )
endif ()
add_llvm_library(MLIRTargetROCDLIR
  LLVMIR/ConvertToROCDLIR.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Target/LLVMIR
  DEPENDS
  intrinsics_gen
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTargetROCDLIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRTargetROCDLIR
  MLIRGPU
  MLIRIR
  MLIRLLVMIR
  MLIRROCDLIR
  MLIRTargetLLVMIRModuleTranslation
  )
endif ()
