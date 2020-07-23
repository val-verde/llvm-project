file(GLOB globbed *.c *.cpp)
add_llvm_library(MLIRStandardOps
  ${globbed}

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/StandardOps
  )
add_dependencies(MLIRStandardOps
  MLIRCallOpInterfacesIncGen
  MLIRStandardOpsIncGen
  MLIRIR
  LLVMSupport
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRStandardOps PUBLIC LLVM)
else ()
target_link_libraries(MLIRStandardOps MLIRIR LLVMSupport)
endif ()
