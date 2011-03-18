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
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		List *del = new List();
		List *list = new List();
		List *var = new List();
		for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
			DEBUG(errs() << *I << "\n");
			Data *data = GetInfo(I);
			if(data->opcode >= 8 && data->opcode <= 25) BinaryProcessing(data, del, list, var);
			else if(data->opcode == 27) LoadProcessing(data, del, list, var);
			else if(data->opcode == 28) StoreProcessing(data, list, var);
			else{
				DeadValueReplacement(data, var);
				delete data;
			}
		}
		DeadInstructionElimination(del);
		delete del;
		delete list;
		delete var;
	}
	DEBUG(errs() << "\n\n--------------------------------------------------------------------------\n\n\n");
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
			DEBUG(errs() << *I << "\n");
		}
	}
	DEBUG(errs() << "\n\n--------------------------------------------------------------------------\n\n\n");
	errs() << "Eliminated:\n\t" << binary << " binary instruction(s)\n\t" << load << " load instruction(s)\n";
	return false;
}