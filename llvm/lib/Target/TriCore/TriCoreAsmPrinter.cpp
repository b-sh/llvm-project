//===-- TriCoreAsmPrinter.cpp - TriCore LLVM assembly writer --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the XAS-format TriCore assembly language.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "TriCore.h"
#include "MCTargetDesc/TriCoreInstPrinter.h"
#include "TriCoreInstrInfo.h"
#include "TriCoreMCInstLower.h"
#include "TriCoreSubtarget.h"
#include "TriCoreTargetMachine.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include <algorithm>
#include <cctype>
using namespace llvm;

namespace {
class TriCoreAsmPrinter : public AsmPrinter {
  TriCoreMCInstLower MCInstLowering;

public:
  explicit TriCoreAsmPrinter(TargetMachine &TM,
                         std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), MCInstLowering(*this) {}

  virtual StringRef getPassName() const override { return "TriCore Assembly Printer"; }

  virtual void emitFunctionEntryLabel() override;
  virtual void emitInstruction(const MachineInstr *MI) override;
  virtual void emitFunctionBodyStart() override;
};
} // end of anonymous namespace

void TriCoreAsmPrinter::emitFunctionBodyStart() {
  MCInstLowering.Initialize(&getObjFileLowering().getMangler(), &MF->getContext());
}

void TriCoreAsmPrinter::emitFunctionEntryLabel() {
  OutStreamer->emitLabel(CurrentFnSym);
}

void TriCoreAsmPrinter::emitInstruction(const MachineInstr *MI) {
  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);

  EmitToStreamer(*OutStreamer, TmpInst);
}

// Force static initialization.
extern "C" void LLVMInitializeTriCoreAsmPrinter() {
  RegisterAsmPrinter<TriCoreAsmPrinter> X(TheTriCoreTarget);
}
