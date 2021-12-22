add_llvm_component_library(LLVMTriCoreDesc
  TriCoreMCTargetDesc.cpp
  TriCoreMCAsmInfo.cpp
  TriCoreMCCodeEmitter.cpp
  TriCoreAsmBackend.cpp
  TriCoreELFObjectWriter.cpp
  TriCoreInstPrinter.cpp

  LINK_COMPONENTS
  MC
  TriCoreInfo
  Support

  ADD_TO_COMPONENT
  TriCore
  )
