add_llvm_library(MLIRSPIRVSerialization
  Deserializer.cpp
  Serializer.cpp
  SPIRVBinaryUtils.cpp
  TranslateRegistration.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/SPIRV
  )

add_dependencies(MLIRSPIRVSerialization
  MLIRSPIRVSerializationGen)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRSPIRVSerialization PUBLIC LLVM)
else ()
target_link_libraries(MLIRSPIRVSerialization
  MLIRIR
  MLIRSPIRV
  MLIRSupport)
endif ()
