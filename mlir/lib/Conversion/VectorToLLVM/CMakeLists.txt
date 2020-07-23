add_llvm_library(MLIRVectorToLLVM
  ConvertVectorToLLVM.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Conversion/VectorToLLVM
)
set(LIBS
  MLIRLLVMIR
  MLIRTransforms
  LLVMCore
  LLVMSupport
  )

add_dependencies(MLIRVectorToLLVM ${LIBS})
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRVectorToLLVM PUBLIC LLVM)
else ()
target_link_libraries(MLIRVectorToLLVM ${LIBS})
endif ()
