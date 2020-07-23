add_llvm_library(MLIRSPIRVTransforms
  DecorateSPIRVCompositeTypeLayoutPass.cpp
  LowerABIAttributesPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/SPIRV
  )

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRSPIRVTransforms PUBLIC LLVM)
else ()
target_link_libraries(MLIRSPIRVTransforms
  MLIRPass
  MLIRSPIRV
  )
endif ()
