//===-- MDSPTargetInfo.cpp - MDSP Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MDSP.h"
#include "llvm/Module.h"
#include "llvm/Target/TargetRegistry.h"
using namespace llvm;

Target llvm::TheMDSPTarget;


extern "C" void LLVMInitializeMDSPTargetInfo()
{
  RegisterTarget<Triple::mdsp> X(TheMDSPTarget, "mdsp", "MDSP");
}

