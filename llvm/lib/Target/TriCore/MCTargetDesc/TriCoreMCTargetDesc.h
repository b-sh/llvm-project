//===-- TriCoreMCTargetDesc.h - TriCore Target Descriptions -----*- C++ -*-===//
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

#ifndef TriCoreMCTARGETDESC_H
#define TriCoreMCTARGETDESC_H

#include "llvm/Config/config.h"
#include "llvm/Support/DataTypes.h"
#include "llvm/MC/MCTargetOptions.h"
#include <memory>

namespace llvm {
class Target;
class MCInstrInfo;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCContext;
class MCCodeEmitter;
class MCAsmInfo;
class MCInstPrinter;
class MCObjectWriter;
class MCAsmBackend;
class MCTargetOptions;
class MCObjectTargetWriter;

class StringRef;
class raw_ostream;
class raw_pwrite_stream;
class Triple;

extern Target TheTriCoreTarget;

MCCodeEmitter *createTriCoreMCCodeEmitter(const MCInstrInfo &MCII,
                                      const MCRegisterInfo &MRI,
                                      MCContext &Ctx);

MCAsmBackend *createTriCoreAsmBackend(const Target &T,
                                               const MCSubtargetInfo &STI,
                                               const MCRegisterInfo &MRI,
                                               const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter>  createTriCoreELFObjectWriter(uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for TriCore registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "TriCoreGenRegisterInfo.inc"

// Defines symbolic names for the TriCore instructions.
//
#define GET_INSTRINFO_ENUM
#include "TriCoreGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "TriCoreGenSubtargetInfo.inc"

#endif
