set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error -Wno-unused-parameter")
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)

if (NOT LLVM_LINK_LLVM_DYLIB)
  set(LIBS
      ${dialect_libs}
      MLIRAffineToStandard
      MLIRLLVMIR
      MLIRSCFToStandard
      MLIRStandardOps
  )

  set(LINK_COMPONENTS
      Support
  )
endif ()

add_flang_library(FortranLower
  CharacterExpr.cpp
  CharacterRuntime.cpp
  Coarray.cpp
  ComplexExpr.cpp
  ConvertType.cpp
  ConvertExpr.cpp
  DoLoopHelper.cpp
  FIRBuilder.cpp
  IntrinsicCall.cpp
  IO.cpp
  Mangler.cpp
  OpenMP.cpp
  PFTBuilder.cpp

  DEPENDS
  FIROptimizer
  ${dialect_libs}

  LINK_LIBS
  ${LIBS}
  FIROptimizer
  FortranCommon
  FortranParser
  FortranEvaluate
  FortranSemantics

  LINK_COMPONENTS
  ${LINK_COMPONENTS}
)
