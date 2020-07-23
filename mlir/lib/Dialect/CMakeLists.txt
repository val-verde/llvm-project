add_subdirectory(AffineOps)
add_subdirectory(FxpMathOps)
add_subdirectory(GPU)
add_subdirectory(Linalg)
add_subdirectory(LLVMIR)
add_subdirectory(LoopOps)
add_subdirectory(QuantOps)
add_subdirectory(SDBM)
add_subdirectory(SPIRV)
add_subdirectory(StandardOps)
add_subdirectory(VectorOps)

add_llvm_library(MLIRDialect
  Traits.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRDialect PUBLIC LLVM)
else ()
target_link_libraries(MLIRDialect MLIRIR)
endif ()
