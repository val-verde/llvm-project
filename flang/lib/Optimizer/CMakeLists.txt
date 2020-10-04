set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-error")
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)

if (NOT LLVM_LINK_LLVM_DYLIB)
  set(LIBS
      ${dialect_libs}
      MLIRTargetLLVMIR
      MLIRTargetLLVMIRModuleTranslation
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

  Support/InternalNames.cpp
  Support/KindMapping.cpp

  Transforms/Inliner.cpp

  DEPENDS
  FIROpsIncGen
  FIROptTransformsPassIncGen
  ${dialect_libs}

  LINK_LIBS
  ${LIBS}

  LINK_COMPONENTS
  ${LINK_COMPONENTS}
)
