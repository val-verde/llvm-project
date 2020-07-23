add_llvm_executable(mlir-edsc-builder-api-test
  builder-api-test.cpp
)

llvm_update_compile_flags(mlir-edsc-builder-api-test)
target_include_directories(mlir-edsc-builder-api-test PRIVATE ..)

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(mlir-edsc-builder-api-test
  PRIVATE
  MLIRAnalysis
  MLIRAffineOps
  MLIREDSC
  MLIRIR
  MLIRLinalg
  MLIRLoopOps
  MLIRStandardOps
  MLIRTransforms
  LLVM
)
else ()
target_link_libraries(mlir-edsc-builder-api-test
  PRIVATE
  MLIRAffineOps
  MLIREDSC
  MLIRIR
  MLIRLinalg
  MLIRLoopOps
  MLIRStandardOps
  MLIRTransforms
  LLVMCore
  LLVMSupport
)
whole_archive_link(mlir-edsc-builder-api-test
  MLIRAffineOps
  MLIRLinalg
  MLIRLoopOps
  MLIRStandardOps
  MLIRTransforms
)
endif ()
