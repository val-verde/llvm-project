set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_library(findAllSymbols
  FindAllSymbols.cpp
  FindAllSymbolsAction.cpp
  FindAllMacros.cpp
  HeaderMapCollector.cpp
  PathConfig.cpp
  PragmaCommentHandler.cpp
  STLPostfixHeaderMap.cpp
  SymbolInfo.cpp

  LINK_LIBS
  clang-cpp
  )

add_subdirectory(tool)
