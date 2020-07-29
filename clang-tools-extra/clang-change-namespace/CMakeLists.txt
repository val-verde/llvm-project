set(LLVM_LINK_COMPONENTS
  support
  )

add_clang_library(clangChangeNamespace
  ChangeNamespace.cpp

  LINK_LIBS
  clang-cpp
  )

add_subdirectory(tool)
