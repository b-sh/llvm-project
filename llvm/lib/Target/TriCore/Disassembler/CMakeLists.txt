add_llvm_component_library(LLVMTriCoreDisassembler
  TriCoreDisassembler.cpp

  LINK_COMPONENTS
  MC
  MCDisassembler
  TriCoreDesc
  TriCoreInfo
  Support

  ADD_TO_COMPONENT
  TriCore
  )
