add_llvm_library(MLIRAnalysis STATIC
  AffineAnalysis.cpp
  AffineStructures.cpp
  CallGraph.cpp
  Dominance.cpp
  InferTypeOpInterface.cpp
  Liveness.cpp
  LoopAnalysis.cpp
  MemRefBoundCheck.cpp
  NestedMatcher.cpp
  OpStats.cpp
  SliceAnalysis.cpp
  TestMemRefDependenceCheck.cpp
  TestParallelismDetection.cpp
  Utils.cpp
  VectorAnalysis.cpp
  Verifier.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Analysis
  )
add_dependencies(MLIRAnalysis
  MLIRAffineOps
  MLIRCallOpInterfacesIncGen
  MLIRTypeInferOpInterfaceIncGen
  MLIRLoopOps
  MLIRVectorOps
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRAnalysis PUBLIC LLVM)
else ()
target_link_libraries(MLIRAnalysis MLIRAffineOps MLIRLoopOps MLIRVectorOps)
endif ()
