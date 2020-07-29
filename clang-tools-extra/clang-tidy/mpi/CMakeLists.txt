set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyMPIModule
  BufferDerefCheck.cpp
  MPITidyModule.cpp
  TypeMismatchCheck.cpp

  LINK_LIBS
  clang-cpp
  )
