//===-- TriCoreSelectionDAGInfo.h - TriCore SelectionDAG Info ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the TriCore subclass for SelectionDAGTargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef TriCoreSELECTIONDAGINFO_H
#define TriCoreSELECTIONDAGINFO_H

#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

namespace llvm {

class TriCoreSelectionDAGInfo : public SelectionDAGTargetInfo {
public:
  ~TriCoreSelectionDAGInfo();
};
}

#endif
