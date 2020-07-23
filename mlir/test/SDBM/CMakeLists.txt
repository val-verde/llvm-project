add_llvm_executable(mlir-sdbm-api-test
  sdbm-api-test.cpp
)

llvm_update_compile_flags(mlir-sdbm-api-test)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(mlir-sdbm-api-test
  PUBLIC
  MLIRIR
  MLIRSDBM
  MLIRSupport
  LLVM
)
else ()
target_link_libraries(mlir-sdbm-api-test
  PRIVATE
  MLIRIR
  MLIRSDBM
  LLVMCore
  LLVMSupport
)
endif ()
whole_archive_link(mlir-sdbm-api-test
  MLIRSDBM
)
target_include_directories(mlir-sdbm-api-test PRIVATE ..)
