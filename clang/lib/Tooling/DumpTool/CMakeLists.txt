
add_clang_executable(clang-ast-dump
  ASTSrcLocProcessor.cpp
  ClangSrcLocDump.cpp
)

target_link_libraries(clang-ast-dump
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangDriver
  clangFrontend
  clangSerialization
  clangToolingCore
)

set(CLANG_AST_DUMP clang-ast-dump CACHE
    STRING "Native clang-ast-dump executable. Saves building one when cross-compiling.")

set(CLANG_AST_DUMP_EXE ${CLANG_AST_DUMP} PARENT_SCOPE)
set(CLANG_AST_DUMP_TARGET clang-ast-dump PARENT_SCOPE)

if(LLVM_USE_HOST_TOOLS)
  if (${CLANG_AST_DUMP} STREQUAL "clang-ast-dump")
    build_native_tool(clang-ast-dump CLANG_AST_DUMP_EXE DEPENDS clang-ast-dump)
    set(CLANG_AST_DUMP ${CLANG_AST_DUMP_EXE} PARENT_SCOPE)

    add_custom_target(clang-ast-dump-host DEPENDS ${CLANG_AST_DUMP_EXE})
    set(CLANG_AST_DUMP_TARGET clang-ast-dump-host DEPENDS PARENT_SCOPE)

    if(NOT LLVM_BUILD_UTILS)
      set_target_properties(clang-ast-dump PROPERTIES EXCLUDE_FROM_ALL ON)
    endif()
  endif()
endif()
