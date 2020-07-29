include_directories(
  ${LLVM_MAIN_SRC_DIR}/lib/Target/AArch64
  ${LLVM_BINARY_DIR}/lib/Target/AArch64
  )

add_library(LLVMExegesisAArch64
  STATIC
  Target.cpp
  )

llvm_update_compile_flags(LLVMExegesisAArch64)
llvm_map_components_to_libnames(libs
  AArch64
  Exegesis
  )

if (NOT LLVM_BUILD_LLVM_DYLIB)
target_link_libraries(LLVMExegesisAArch64 ${libs})
endif ()

set_target_properties(LLVMExegesisAArch64 PROPERTIES FOLDER "Libraries")
