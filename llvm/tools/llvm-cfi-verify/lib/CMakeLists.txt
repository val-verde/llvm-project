add_library(LLVMCFIVerify
  STATIC
  FileAnalysis.cpp
  FileAnalysis.h
  GraphBuilder.cpp
  GraphBuilder.h
  )

llvm_update_compile_flags(LLVMCFIVerify)
llvm_map_components_to_libnames(libs
  DebugInfoDWARF
  MC
  MCParser
  Object
  Support
  Symbolize
  )

if (NOT LLVM_BUILD_LLVM_DYLIB)
target_link_libraries(LLVMCFIVerify ${libs})
endif ()

set_target_properties(LLVMCFIVerify PROPERTIES FOLDER "Libraries")
