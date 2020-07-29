include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_clang_tool(find-all-symbols
  FindAllSymbolsMain.cpp
  )

clang_target_link_libraries(find-all-symbols
  PRIVATE
  clang-cpp
  )
target_link_libraries(find-all-symbols
  PRIVATE
  findAllSymbols
  )

install(PROGRAMS run-find-all-symbols.py
  DESTINATION share/clang
  COMPONENT find-all-symbols)
