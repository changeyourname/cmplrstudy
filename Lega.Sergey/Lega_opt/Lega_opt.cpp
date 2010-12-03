//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "LegaSergey_Opt"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Streams.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

STATISTIC(TestPassCounter, "Counts number of functions greeted");

namespace {
  // Test - The first implementation, without getAnalysisUsage.
  struct TestStruct : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    TestStruct() : FunctionPass(&ID) {}

    virtual bool runOnFunction(Function &F) {
      TestPassCounter++;
      std::string fname = F.getName();
      EscapeString(fname);
      cerr << "TestPass: " << fname << "\n";
      return false;
    }
  };
}

char TestStruct::ID = 0;
static RegisterPass<Test> X("Opt", "TestPass");

namespace {
  // TestStruct2 - The second implementation with getAnalysisUsage implemented.
  struct TestStruct2 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    TestStruct2() : FunctionPass(&ID) {}

    virtual bool runOnFunction(Function &F) {
      TestPassCounter++;
      std::string fname = F.getName();
      EscapeString(fname);
      cerr << "TestPass: " << fname << "\n";
      return false;
    }

    // We don't modify the program, so we preserve all analyses
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    };
  };
}

char Hello2::ID = 0;
static RegisterPass<TestStruct2>
Y("TestStruct2", "TestPass (with getAnalysisUsage implemented)");
