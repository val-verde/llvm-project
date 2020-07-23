add_llvm_library(MLIRTestIR
  TestFunc.cpp
  TestMatchers.cpp
  TestSymbolUses.cpp

  ADDITIONAL_HEADER_DIRS
  )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../TestDialect)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../TestDialect)
add_dependencies(MLIRTestIR
  MLIRTestDialect
)
if (LLVM_LINK_LLVM_DYLIB)
target_link_libraries(MLIRTestIR PUBLIC LLVM)
else ()
target_link_libraries(MLIRTestIR
  MLIRPass
  )
endif ()
