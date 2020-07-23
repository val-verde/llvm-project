add_llvm_library(MLIRGPUtoROCDLTransforms
  LowerGpuOpsToROCDLOps.cpp
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRGPUtoROCDLTransforms PUBLIC LLVM)
else ()
target_link_libraries(MLIRGPUtoROCDLTransforms
  LLVMSupport
  MLIRGPU
  MLIRLLVMIR
  MLIRROCDLIR
  MLIRPass
  )
endif ()
