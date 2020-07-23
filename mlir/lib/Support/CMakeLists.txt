set(LLVM_OPTIONAL_SOURCES
  FileUtilities.cpp
  JitRunner.cpp
  MlirOptMain.cpp
  StorageUniquer.cpp
  ToolUtilities.cpp
  TranslateClParser.cpp
)

add_llvm_library(MLIRSupport
  FileUtilities.cpp
  StorageUniquer.cpp
  ToolUtilities.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Support
  )

if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRSupport PUBLIC LLVM)
else ()
target_link_libraries(MLIRSupport LLVMSupport ${LLVM_PTHREAD_LIB})
endif ()

add_llvm_library(MLIROptMain
  MlirOptMain.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Support
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIROptMain PUBLIC LLVM)
else ()
target_link_libraries(MLIROptMain
  MLIRPass
  LLVMSupport
  MLIRSupport
  )
endif ()

add_llvm_library(MLIRTranslateClParser
  TranslateClParser.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Support
  )
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTranslateClParser PUBLIC LLVM)
else ()
target_link_libraries(MLIRTranslateClParser LLVMSupport)
endif ()

add_llvm_library(MLIRJitRunner
  JitRunner.cpp
)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRJitRunner PUBLIC LLVM)
else ()
target_link_libraries(MLIRJitRunner PRIVATE
  MLIRExecutionEngine
  MLIRIR
  MLIRParser
  MLIRStandardOps
  MLIRTargetLLVMIR
  MLIRTransforms
  MLIRStandardToLLVM
  MLIRSupport
  LLVMCore
  LLVMSupport
)
endif ()
