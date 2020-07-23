add_llvm_library(MLIRTestPass
  TestPassManager.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Pass
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTestPass PUBLIC LLVM)
else ()
target_link_libraries(MLIRTestPass
  MLIRIR
  MLIRPass
  )
endif ()
