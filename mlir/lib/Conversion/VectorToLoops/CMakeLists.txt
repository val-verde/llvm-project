add_llvm_library(MLIRVectorToLoops
  ConvertVectorToLoops.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Conversion/VectorToLoops
)
set(LIBS
  MLIRLLVMIR
  MLIRTransforms
  LLVMCore
  LLVMSupport
  )

add_dependencies(MLIRVectorToLoops ${LIBS})
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRVectorToLoops PUBLIC LLVM)
else ()
target_link_libraries(MLIRVectorToLoops ${LIBS})
endif ()
