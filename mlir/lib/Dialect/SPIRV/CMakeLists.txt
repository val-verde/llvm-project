set(LLVM_TARGET_DEFINITIONS SPIRVCanonicalization.td)
mlir_tablegen(SPIRVCanonicalization.inc -gen-rewriters)
add_public_tablegen_target(MLIRSPIRVCanonicalizationIncGen)

add_llvm_library(MLIRSPIRV
  DialectRegistration.cpp
  LayoutUtils.cpp
  SPIRVDialect.cpp
  SPIRVOps.cpp
  SPIRVLowering.cpp
  SPIRVTypes.cpp
  TargetAndABI.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/SPIRV
  )

add_dependencies(MLIRSPIRV
  MLIRSPIRVAvailabilityIncGen
  MLIRSPIRVCanonicalizationIncGen
  MLIRSPIRVEnumAvailabilityIncGen
  MLIRSPIRVEnumsIncGen
  MLIRSPIRVOpsIncGen
  MLIRSPIRVOpUtilsGen
  MLIRSPIRVTargetAndABIIncGen)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRSPIRV PUBLIC LLVM)
else ()
target_link_libraries(MLIRSPIRV
  MLIRIR
  MLIRParser
  MLIRSupport
  MLIRTransforms)
endif ()

add_subdirectory(Serialization)
add_subdirectory(Transforms)
