add_llvm_library(MLIRVectorOps
  DialectRegistration.cpp
  VectorOps.cpp
  VectorTransforms.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/VectorOps
  )

add_dependencies(MLIRVectorOps MLIRVectorOpsIncGen)
add_dependencies(MLIRVectorOps MLIRVectorTransformPatternsIncGen)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRVectorOps PUBLIC LLVM)
else ()
target_link_libraries(MLIRVectorOps MLIRIR)
endif ()
