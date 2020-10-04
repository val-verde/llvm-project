get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)

if (NOT LLVM_LINK_LLVM_DYLIB)
  set(LIBS
      ${dialect_libs}
      MLIRLLVMToLLVMIRTranslation
      MLIRTargetLLVMIRExport
  )
  set(LINK_COMPONENTS
      AsmParser
      AsmPrinter
      Remarks
  )
endif ()

add_flang_library(FIROptimizer
  Dialect/FIRAttr.cpp
  Dialect/FIRDialect.cpp
  Dialect/FIROps.cpp
  Dialect/FIRType.cpp

  Support/FIRContext.cpp
  Support/InternalNames.cpp
  Support/KindMapping.cpp

  CodeGen/CGOps.cpp
  CodeGen/PreCGRewrite.cpp

  Transforms/Inliner.cpp

  DEPENDS
  FIROpsIncGen
  FIROptCodeGenPassIncGen
  FIROptTransformsPassIncGen
  CGOpsIncGen
  ${dialect_libs}

  LINK_LIBS
  ${LIBS}

  LINK_COMPONENTS
  ${LINK_COMPONENTS}
)
