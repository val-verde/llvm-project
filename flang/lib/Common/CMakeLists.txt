if (NOT LLVM_LINK_LLVM_DYLIB)
  set (LIBS
       Support)
endif ()

add_flang_library(FortranCommon
  Fortran.cpp
  Fortran-features.cpp
  default-kinds.cpp
  idioms.cpp

  LINK_COMPONENTS
  ${LIBS}
)
