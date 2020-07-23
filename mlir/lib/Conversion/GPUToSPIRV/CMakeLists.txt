add_llvm_library(MLIRGPUtoSPIRVTransforms
  ConvertGPUToSPIRV.cpp
  ConvertGPUToSPIRVPass.cpp
  )

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRGPUtoSPIRVTransforms PUBLIC LLVM)
else ()
target_link_libraries(MLIRGPUtoSPIRVTransforms
  MLIRGPU
  MLIRIR
  MLIRPass
  MLIRSPIRV
  MLIRStandardOps
  MLIRStandardToSPIRVTransforms
  MLIRSupport
  MLIRTransforms
  )
endif ()
