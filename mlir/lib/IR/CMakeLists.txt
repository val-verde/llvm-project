file(GLOB globbed *.c *.cpp)
add_llvm_library(MLIRIR
  ${globbed}

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/IR
  )
add_dependencies(MLIRIR MLIRCallOpInterfacesIncGen MLIROpAsmInterfacesIncGen MLIRSupport LLVMSupport)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRIR MLIRSupport LLVMSupport)
endif ()
