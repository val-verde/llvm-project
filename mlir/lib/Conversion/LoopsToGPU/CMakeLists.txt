set(LIBS
  MLIRAffineOps
  MLIRGPU
  MLIRIR
  MLIRLinalg
  MLIRPass
  MLIRStandardOps
  MLIRSupport
  MLIRTransforms
  LLVMSupport
)

add_llvm_library(MLIRLoopsToGPU
  LoopsToGPU.cpp
  LoopsToGPUPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Conversion/LoopsToGPU
)
add_dependencies(MLIRLoopsToGPU ${LIBS})
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRLoopsToGPU PUBLIC LLVM)
else ()
target_link_libraries(MLIRLoopsToGPU ${LIBS})
endif ()
