add_llvm_library(MLIRParser
  Lexer.cpp
  Parser.cpp
  Token.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Parser
  )
add_dependencies(MLIRParser MLIRIR MLIRAnalysis)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRParser PUBLIC LLVM)
else ()
target_link_libraries(MLIRParser MLIRIR MLIRAnalysis)
endif ()
