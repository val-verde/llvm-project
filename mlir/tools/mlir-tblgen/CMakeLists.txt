if(NOT LLVM_LINK_LLVM_DYLIB)
set(LLVM_LINK_COMPONENTS
  Demangle
  Support
  TableGen
  )
endif()

add_tablegen(mlir-tblgen MLIR
  DialectGen.cpp
  DirectiveCommonGen.cpp
  EnumsGen.cpp
  LLVMIRConversionGen.cpp
  LLVMIRIntrinsicGen.cpp
  mlir-tblgen.cpp
  OpDefinitionsGen.cpp
  OpDocGen.cpp
  OpFormatGen.cpp
  OpInterfacesGen.cpp
  OpPythonBindingGen.cpp
  PassCAPIGen.cpp
  PassDocGen.cpp
  PassGen.cpp
  RewriterGen.cpp
  SPIRVUtilsGen.cpp
  StructsGen.cpp
  TypeDefGen.cpp
  )

set_target_properties(mlir-tblgen PROPERTIES FOLDER "Tablegenning")
target_link_libraries(mlir-tblgen
  PRIVATE
  MLIRSupportIndentedOstream
  MLIRTableGen)

mlir_check_all_link_libraries(mlir-tblgen)
