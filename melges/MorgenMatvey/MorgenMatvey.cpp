//Здесь был страшный header от создателей LLVM :)
#define DEBUG_TYPE "MorgenMatvey"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

STATISTIC(SomeCounter, "Counts number of functions greeted");

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct TestStruct : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    TestStruct() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      ++SomeCounter;
      errs() << "LLVM says that your name: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }
  };
}

char TestStruct::ID = 0;
static RegisterPass<TestStruct> X("Opt", "Hello World Pass");

namespace {
  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct TestStruct2 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    TestStruct2() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      ++SomeCounter;
      errs() << "LLVM says that your name: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }

    // We don't modify the program, so we preserve all analyses
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
  };
}

char TestStruct2::ID = 0;
static RegisterPass<TestStruct2>
Y("Opt2", "Hello World Pass (with getAnalysisUsage implemented)");
