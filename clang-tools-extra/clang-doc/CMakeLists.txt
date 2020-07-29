set(LLVM_LINK_COMPONENTS
  support
  BitstreamReader
  )

add_clang_library(clangDoc
  BitcodeReader.cpp
  BitcodeWriter.cpp
  ClangDoc.cpp
  Generators.cpp
  HTMLGenerator.cpp
  Mapper.cpp
  MDGenerator.cpp
  Representation.cpp
  Serialize.cpp
  YAMLGenerator.cpp

  LINK_LIBS
  clang-cpp
  )

add_subdirectory(tool)
