add_llvm_library(MLIRAffineOps
  AffineOps.cpp
  DialectRegistration.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/AffineOps
  )
add_dependencies(MLIRAffineOps
  MLIRAffineOpsIncGen
  MLIRIR
  MLIRLoopLikeInterfaceIncGen
  MLIRStandardOps)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRAffineOps PUBLIC LLVM)
else ()
target_link_libraries(MLIRAffineOps MLIRIR MLIRStandardOps)
endif ()

