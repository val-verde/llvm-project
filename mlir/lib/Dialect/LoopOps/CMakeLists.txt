file(GLOB globbed *.c *.cpp)
add_llvm_library(MLIRLoopOps
  ${globbed}

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/LoopOps
  )
add_dependencies(MLIRLoopOps MLIRLoopLikeInterfaceIncGen MLIRLoopOpsIncGen MLIRStandardOps LLVMSupport)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRLoopOps PUBLIC LLVM)
else ()
target_link_libraries(MLIRLoopOps LLVMSupport)
endif ()
