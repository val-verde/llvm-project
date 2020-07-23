add_llvm_library(MLIRSDBM
  SDBM.cpp
  SDBMExpr.cpp
  SDBMDialect.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/SDBM
)
add_dependencies(MLIRSDBM MLIRIR)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRSDBM PUBLIC LLVM)
else ()
target_link_libraries(MLIRSDBM MLIRIR)
endif ()
