add_llvm_library(MLIRLinalgToLLVM
  LinalgToLLVM.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Conversion/LinalgToLLVM
)
set(LIBS
  MLIRLLVMIR
  MLIRTransforms
  LLVMCore
  LLVMSupport
  )

add_dependencies(MLIRLinalgToLLVM ${LIBS})
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRLinalgToLLVM PUBLIC LLVM)
else ()
target_link_libraries(MLIRLinalgToLLVM ${LIBS})
endif ()
