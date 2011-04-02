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

//Struct, which contains Instruction information
struct Data{
	unsigned int opcode, num;
	Instruction *I;
	Value *operands[32];
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
void DeadValueReplacement(Data *data, List *var);
void ProcessingBinary(Data *data, List *del,  List *list, List *var);
void ProcessingLoad(Data *data, List *del,  List *list, List * var);
void ProcessingStore(Data *data, List *list, List *var);

//Make Basic Block's Input List functions
void MakeAllInputLists(BasicBlockInfo **table);
void MakeLoad(Data *data,  List *list);
void MakeBinary(Data *data, List *list);
void MakeListOut(BasicBlock *BB, List *list_in, List *list_out);
void MakeStore(Data *data, List *list);

//Print functions
void PrintDataList(List *list);
void PrintDelList(List *list);
void PrintVarList(List *list);
void PrintFunction(Function &F);

//Another functions
Data* GetInfo(Instruction *I);
int GetNumByID(BasicBlock *BB, BasicBlockInfo **table);
void CreateBasicBlockTable(Function &F, BasicBlockInfo **table);



///CSE::FUNCTION'S DEFINITION

bool CSE::runOnFunction(Function &F){
	errs() << "Function: " << F.getName() << "\n";
	DEBUG(PrintFunction(F));

	bb_number = F.size();

	BasicBlockInfo **table = new BasicBlockInfo*[bb_number];
	unsigned int i;

	CreateBasicBlockTable(F, table);
	
	MakeAllInputLists(table);

	List *var = new List();

	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		BasicBlockInfo *info = table[GetNumByID(BB, table)];
		LocalCSE(BB, info->list, var);
	}

	delete var;

	for(i = 0; i < bb_number; i++) delete table[i];
	delete table;

	DEBUG(PrintFunction(F));
	errs() << "   " << binary << " binary instruction(s) eliminated\n";
	errs() << "   " << load << " load instruction(s) eliminated\n\n\n";
	binary = 0;
	load = 0;
	return false;
}