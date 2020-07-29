set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangReorderFields
  ReorderFieldsAction.cpp

  LINK_LIBS
  clang-cpp
  )

add_subdirectory(tool)
