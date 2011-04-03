#pragma once


#include <assert.h>
#include "List.h"
#include "llvm/Constant.h"
#include "llvm/Function.h"
#include "llvm/Instruction.h"
#include "llvm/Pass.h"
#include "llvm/Value.h"
#include "llvm/Analysis/ProfileInfo.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"


using namespace llvm;



///DATA TYPES

//CSE struct
namespace{
	struct CSE:public FunctionPass{
		static char ID;
		CSE() : FunctionPass(ID){
			initializeCSEPass(*PassRegistry::getPassRegistry());
		}
		virtual bool runOnFunction(Function &F);
	};
}

//Struct, which contains Basic Block Input List
struct BasicBlockInfo{
	BasicBlock *id;
	List *list;
};

//Class, which contains Instruction information
class Data{
	public:
		unsigned int opcode, num;
		Instruction *I;
		Value **operands;
		Data(Instruction *I);
		~Data();
		void DeadValueReplacement(List *var);
		void ProcessingBinary(List *del,  List *list, List *var);
		void ProcessingLoad(List *del,  List *list, List * var);
		void ProcessingStore(List *list, List *var);
};

//Struct, which contains information about equal variables
struct Var{
	Value *res, *arg;
};


///GLOBAL VARIABLES

char CSE::ID = 0;
unsigned int bb_number, binary, load;



///FUNCTION'S DECLARATIONS

//List functions
bool ListComparison(List *list1, List *list2);
List* ListIntersection(List *list1, List *list2);
void ListCopy(List *src, List *dst);

//Local CSE functions
void LocalCSE(BasicBlock *BB, List *list_input, List *var);
void DeadInstructionElimination(List *del);

//Make Basic Block's Input List functions
void MakeAllInputLists(BasicBlockInfo **table);
void MakeListOut(BasicBlock *BB, List *list_in, List *list_out);

//Print functions
void PrintDataList(List *list);
void PrintDelList(List *list);
void PrintVarList(List *list);
void PrintFunction(Function &F);

//Another functions
int GetNumByID(BasicBlock *BB, BasicBlockInfo **table);
void CreateBasicBlockTable(Function &F, BasicBlockInfo **table);