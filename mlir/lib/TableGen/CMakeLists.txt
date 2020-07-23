add_llvm_library(LLVMMLIRTableGen DISABLE_LLVM_LINK_LLVM_DYLIB
  Argument.cpp
  Attribute.cpp
  Constraint.cpp
  Dialect.cpp
  Format.cpp
  Operator.cpp
  OpInterfaces.cpp
  OpTrait.cpp
  Pattern.cpp
  Predicate.cpp
  Type.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/TableGen
  )
if (NOT LLVM_LINK_LLVM_DYLIB)
target_link_libraries(LLVMMLIRTableGen LLVMSupport LLVMTableGen)
endif ()
