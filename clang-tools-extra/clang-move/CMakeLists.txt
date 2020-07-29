set(LLVM_LINK_COMPONENTS
  support
  )

add_clang_library(clangMove
  Move.cpp
  HelperDeclRefGraph.cpp

  LINK_LIBS
  clang-cpp
  )

add_subdirectory(tool)
