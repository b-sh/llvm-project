//===-- TriCoreMCTargetDesc.cpp - TriCore Target Descriptions -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TriCore specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "TriCoreMCTargetDesc.h"
#include "TriCoreInstPrinter.h"
#include "TriCoreMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "TriCoreGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TriCoreGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TriCoreGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createTriCoreMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTriCoreMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createTriCoreMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTriCoreMCRegisterInfo(X, TriCore::A11);
  return X;
}

static MCSubtargetInfo *createTriCoreMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  return createTriCoreMCSubtargetInfoImpl(TT, CPU, "", FS);
}

static MCAsmInfo *createTriCoreMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  return new TriCoreMCAsmInfo(TT);
}

static MCInstPrinter *
createTriCoreMCInstPrinter(const Triple &TT, unsigned SyntaxVariant,
                       const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI) {
  return new TriCoreInstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeTriCoreTargetMC() {
  // Register the MC asm info.
  TargetRegistry::RegisterMCAsmInfo(TheTriCoreTarget, createTriCoreMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTriCoreTarget, createTriCoreMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTriCoreTarget, createTriCoreMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTriCoreTarget,
                                          createTriCoreMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheTriCoreTarget, createTriCoreMCInstPrinter);

  // Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(TheTriCoreTarget, createTriCoreAsmBackend);

  // Register the MCCodeEmitter
  TargetRegistry::RegisterMCCodeEmitter(TheTriCoreTarget, createTriCoreMCCodeEmitter);
}
