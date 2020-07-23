add_llvm_library(MLIRLLVMIR
  IR/LLVMDialect.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/LLVMIR
  )
add_dependencies(MLIRLLVMIR MLIRLLVMOpsIncGen MLIRLLVMConversionsIncGen LLVMAsmParser LLVMCore LLVMSupport)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRLLVMIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRLLVMIR LLVMAsmParser LLVMCore LLVMSupport MLIRIR)
endif ()

add_llvm_library(MLIRNVVMIR
  IR/NVVMDialect.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/LLVMIR
  )
add_dependencies(MLIRNVVMIR MLIRNVVMOpsIncGen MLIRNVVMConversionsIncGen LLVMAsmParser LLVMCore LLVMSupport)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRNVVMIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRNVVMIR LLVMAsmParser LLVMCore LLVMSupport MLIRIR)
endif ()
add_llvm_library(MLIRROCDLIR
  IR/ROCDLDialect.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/LLVMIR
  )
add_dependencies(MLIRROCDLIR MLIRROCDLOpsIncGen MLIRROCDLConversionsIncGen LLVMAsmParser LLVMCore LLVMSupport)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRROCDLIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRROCDLIR LLVMAsmParser LLVMCore LLVMSupport MLIRIR)
endif ()
