#define DEBUG_TYPE "cse"


#include "CommonSubexpressionElimination.h"


namespace{
	struct CSE:public FunctionPass{
		static char ID;
		CSE() : FunctionPass(ID){
			initializeCSEPass(*PassRegistry::getPassRegistry());
		}
		virtual bool runOnFunction(Function &F);
	};
}


char CSE::ID = 0;


INITIALIZE_PASS(CSE, "cse", "CommonSubexpressionElimination", false, false)


FunctionPass *llvm::createCSEPass(){
	return new CSE();
}


bool CSE::runOnFunction(Function &F){
	errs() << "Function: " << F.getName() << "\n";
	DEBUG(PrintFunction(F));

	bb_number = F.size();

	BasicBlockInfo **table = new BasicBlockInfo*[bb_number];
	unsigned int i;

	CreateBasicBlockTable(F, table);
	
	MakeAllInputLists(table);

	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		BasicBlockInfo *info = table[GetNumByID(BB, table)];
		LocalCSE(BB, info->list);
	}

	for(i = 0; i < bb_number; i++) delete table[i];
	delete table;

	DEBUG(PrintFunction(F));
	errs() << "   " << binary << " binary instruction(s) eliminated\n";
	errs() << "   " << load << " load instruction(s) eliminated\n\n\n";
	binary = 0;
	load = 0;
	return false;
}