add_llvm_library(MLIRTranslation
  Translation.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Translation
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTranslation PUBLIC LLVM)
else ()
target_link_libraries(MLIRTranslation LLVMSupport)
endif ()
