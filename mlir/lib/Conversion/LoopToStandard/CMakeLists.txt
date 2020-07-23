add_llvm_library(MLIRLoopToStandard
  ConvertLoopToStandard.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Conversion/LoopToStandard
)
add_dependencies(
  MLIRLoopToStandard

  MLIRLoopOps
  MLIRTransforms
  LLVMCore
  LLVMSupport
)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRLoopToStandard PUBLIC LLVM)
else ()
target_link_libraries(
  MLIRLoopToStandard

  MLIRLoopOps
  MLIRTransforms
  LLVMCore
  LLVMSupport
)
endif ()
