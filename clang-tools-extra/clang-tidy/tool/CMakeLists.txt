set(LLVM_LINK_COMPONENTS
  AllTargetsAsmParsers
  AllTargetsDescs
  AllTargetsInfos
  support
  )

add_clang_tool(clang-tidy
  ClangTidyMain.cpp
  )
add_dependencies(clang-tidy
  clang-resource-headers
  )
clang_target_link_libraries(clang-tidy
  PRIVATE
  clang-cpp
  )
target_link_libraries(clang-tidy
  PRIVATE
  ${ALL_CLANG_TIDY_CHECKS}
  )


install(PROGRAMS clang-tidy-diff.py
  DESTINATION share/clang
  COMPONENT clang-tidy)
install(PROGRAMS run-clang-tidy.py
  DESTINATION share/clang
  COMPONENT clang-tidy)
