file(GLOB globbed *.c *.cpp)
add_llvm_library(MLIRPass
  ${globbed}

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Pass
  )
add_dependencies(MLIRPass MLIRAnalysis MLIRIR LLVMSupport)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRPass PUBLIC LLVM)
else ()
target_link_libraries(MLIRPass MLIRAnalysis MLIRIR LLVMSupport)
endif ()
