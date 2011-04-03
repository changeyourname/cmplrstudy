#define DEBUG_TYPE "cse"


#include "CommonSubexpressionElimination.h"


INITIALIZE_PASS(CSE, "cse", "CommonSubexpressionElimination", false, false)


FunctionPass *llvm::createCSEPass(){
	return new CSE();
}



///CSE::FUNCTION'S DEFINITION

bool CSE::runOnFunction(Function &F){
	errs() << "Function: " << F.getName() << "\n";
	DEBUG(PrintFunction(F));

	bb_number = F.size();
	binary = 0;
	load = 0;

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
	return false;
}



///DATA::FUNCTION'S DEFINITION

Data::Data(Instruction *ins){
	unsigned int i;
	I = ins;
	opcode = ins->getOpcode();
	num = ins->getNumOperands();
	operands = new Value*[num];
	for(i = 0; i < num; i++) operands[i] = ins->getOperand(i);
}

Data::~Data(){
	delete operands;
}

//Replace dead variables
void Data::DeadValueReplacement(List *var){
	unsigned int i;
	Node *node = var->GetFirst();
	while(node != NULL){
		Var *v = (Var*) node->data;
		for(i = 0; i < num; i++){
			if(operands[i] == v->res){
				I->setOperand(i, v->arg);
				operands[i] = v->arg;
			}
		}
		node = node->next;
	}
}

/*Function, which process Binary Instructions in Local CSE
First, this function replace dead values in Instruction
After that it check Instruction in List.
If we have similar Instruction in List, we can remove this and we get new equal variable's pair
Note: if del == var == NULL we use this function only to create Output List (used in MakeListOut function)
*/
void Data::ProcessingBinary(List *del,  List *list, List *var){
	bool flag = false;
	if(var != NULL) DeadValueReplacement(var);
	Node *node = list->GetFirst();
	while(node != NULL){
		Data *dt = (Data*) node->data;
		if(opcode == dt->opcode){
			if(operands[0] == dt->operands[0] && operands[1] == dt->operands[1]){
				if(var != NULL && del != NULL){
					Instruction **i = new Instruction*;
					Var *v = new Var();
					*i = I;
					v->res = I;
					v->arg = dt->I;
					del->AddToEnd(i);
					var->AddToEnd(v);
					binary++;
				}
				flag = true;
			}
			if(opcode == Instruction::Add
				|| opcode == Instruction::FAdd
				|| opcode == Instruction::Mul
				|| opcode == Instruction::FMul
				|| opcode == Instruction::And
				|| opcode == Instruction::Or
				|| opcode == Instruction::Xor){
				if(operands[0] == dt->operands[1] && operands[1] == dt->operands[0]){
					if(var != NULL && del != NULL){
						Instruction **i = new Instruction*;
						Var *v = new Var();
						*i = I;
						v->res = I;
						v->arg = dt->I;
						del->AddToEnd(i);
						var->AddToEnd(v);
						binary++;
					}
					flag = true;
				}
			}
		}
		node = node->next;
	}
	if(flag == false) list->AddToEnd(this);
}

/*Function, which process Load Instructions in Local CSE
This function check Load Instruction in List.
If we have similar one, we can remove this and we get new equal variable's pair
Note: if del == var == NULL we use this function only to create Output List (used in MakeListOut function)
*/
void Data::ProcessingLoad(List *del,  List *list, List * var){
	bool flag = false;
	Node *node = list->GetFirst();
	while(node != NULL){
		Data *dt = (Data*) node->data;
		if(dt->opcode == Instruction::Load){
			if(dt->operands[0] == operands[0]){
				if(var != NULL && del != NULL){
					Instruction **i = new Instruction*;
					Var *v = new Var();
					*i = I;
					v->res = I;
					v->arg = dt->I;
					del->AddToEnd(i);
					var->AddToEnd(v);
					load++;
				}
				flag = true;
				break;
			}
		}
		node = node->next;
	}
	if(flag == false) list->AddToEnd(this);
}

/*Function, which process Store Instructions in Local CSE
First, this function replace dead values in Instruction
After that it delete all Instructions which contain variable we stored into
Note: if var == NULL we use this function only to create Output List (used in MakeListOut function)
*/
void Data::ProcessingStore(List *list, List *var){
	unsigned int i;
	if(var != NULL) DeadValueReplacement(var);
	Node *node = list->GetFirst();
	while(node != NULL){
		bool flag = false;
		Data *d = (Data*) node->data;
		for(i = 0; i < d->num; i++){
			if(d->operands[i] == operands[1]){
				Node *n = node->next;
				list->DelNode(node);
				node = n;
				flag = true;
				break;
			}
		}
		if(flag == false) node = node->next;
	}
	delete this;
}



///LIST'S FUNCTIONS

//Check Lists equality (only for Lists of Data)
bool ListComparison(List *list1, List *list2){
	Data *data1, *data2;
	Node *node1, *node2;
	unsigned int size1, size2;
	size1 = 0;
	size2 = 0;
	for(node1 = list1->GetFirst(); node1 != 0; node1 = node1->next) size1++;
	for(node2 = list2->GetFirst(); node2 != 0; node2 = node2->next) size2++;
	if(size1 != size2) return false;
	for(node1 = list1->GetFirst(); node1 != 0; node1 = node1->next){
		data1 = (Data*) node1->data;
		for(node2 = list2->GetFirst(); node2 != 0; node2 = node2->next){
			data2 = (Data*) node2->data;
			if(data1->I == data2->I){
				size1--;
				break;
			}
		}
	}
	if(size1 == 0) return true;
	else false;
}

//Find List's intersection (only for Lists of Data)
List* ListIntersection(List *list1, List *list2){
	List *intersection = new List();
	Data *data1, *data2;
	Node *node1, *node2;
	for(node1 = list1->GetFirst(); node1 != 0; node1 = node1->next){
		data1 = (Data*) node1->data;
		for(node2 = list2->GetFirst(); node2 != 0; node2 = node2->next){
			data2 = (Data*) node2->data;
			if(data1->I == data2->I){
				Data *data = new Data(data1->I);
				intersection->AddToEnd(data);
				break;
			}
		}
	}
	return intersection;
}

//Copy List (only for Lists of Data)
void ListCopy(List *src, List *dst){
	Node *node;
	for(node = src->GetFirst(); node != 0; node = node->next){
		Data *data_src = (Data*) node->data;
		Data *data_dst = new Data(data_src->I);
		dst->AddToEnd(data_dst);
	}
}



///LOCAL CSE'S FUNCTIONS

/*Main Local CSE function
This function look through all Basic Block's Instructions and process them. 
At the end it delete all dead Instructions.
list_input - Input List of Basic Block, but Local CSE change it while work
var - List of equal variables (it is one for all Basic Blocks)
del - List of dead Instruction
*/
void LocalCSE(BasicBlock *BB, List *list_input, List *var){
	List *del = new List();
	for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
		Data *data = new Data(I);
		if(data->opcode >= Instruction::Add && data->opcode <= Instruction::Xor) data->ProcessingBinary(del, list_input, var);
		else if(data->opcode == Instruction::Load) data->ProcessingLoad(del, list_input, var);
		else if(data->opcode == Instruction::Store) data->ProcessingStore(list_input, var);
		else{
			data->DeadValueReplacement(var);
			delete data;
		}
	}
	DeadInstructionElimination(del);
	delete del;
	delete list_input;
}

//Eliminate dead Instructions
void DeadInstructionElimination(List *del){
	Node *node = del->GetFirst();
	while(node != 0){
		Instruction **I = (Instruction**) node->data;
		(*I)->eraseFromParent();
		node = node->next;
	}
}



///MAKELIST'S FUNCTIONS

//Function, which calculate Input Lists for all Basic Blocks
void MakeAllInputLists(BasicBlockInfo **table){
	List *queue = new List();

	List *entry_list = new List();
	table[0]->list = entry_list;
	queue->AddToEnd(table[0]);

	//We pass all Basic Blocks
	while(queue->IsEmpty() == false){
		BasicBlockInfo *BBI = (BasicBlockInfo*) queue->GetFirst()->data;
		queue->ClrFirst();
		List *list_out = new List();
		ListCopy(BBI->list, list_out);

		//Make Output List for current Basic Block
		MakeListOut(BBI->id, BBI->list, list_out);

		DEBUG(errs() << BBI->id->getName() << "\n");
		DEBUG(PrintDataList(BBI->list));
		DEBUG(errs() << "\n");
		DEBUG(PrintDataList(list_out));
		DEBUG(errs() << "---\n");

		//We look through all Successors of Basic Block
		for(succ_iterator SUCC = succ_begin(BBI->id); SUCC != succ_end(BBI->id); SUCC++){
			BasicBlockInfo *info = table[GetNumByID(*SUCC, table)];
			//If we didn't visit this Successor: it's Input List is our Output List
			if(info->list == NULL){
				List *list = new List();
				ListCopy(list_out, list);
				info->list = list;
				queue->AddToEnd(info);
			}
			//If we visited this Successor: it's Input List is intersection with our Output List
			else{
				List *intersection = ListIntersection(list_out, info->list);
				//If we have some changes in Successor's Input List, we should process it once again
				if(ListComparison(intersection, info->list) == false){
					delete info->list;
					info->list = intersection;
					queue->AddToEnd(info);
				}
				else delete intersection;
			}
		}
		delete list_out;
	}
	delete queue;
}

/*Function, which make Output List of Basic Block
We use for it Local CSE functions with del == var == NULL
*/
void MakeListOut(BasicBlock *BB, List *list_in, List *list_out){
	for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
		Data *data = new Data(I);
		if(data->opcode >= Instruction::Add && data->opcode <= Instruction::Xor) data->ProcessingBinary(NULL, list_out, NULL);
		else if(data->opcode == Instruction::Load) data->ProcessingLoad(NULL, list_out, NULL);
		else if(data->opcode == Instruction::Store) data->ProcessingStore(list_out, NULL);
		else delete data;
	}
}



///PRINT FUNCTIONS

//Print List (only for Lists of Data)
void PrintDataList(List *list){
	Node *node;
	for(node = list->GetFirst(); node != 0; node = node->next){
		Data *data = (Data*) node->data;
		errs() << *(data->I) << "\n";
	}
}


//Print all function's Instructions
void PrintFunction(Function &F){
	errs() << "\n\n--------------------------------------------------------------------------\n\n\n";
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		errs() << "\t\t" << BB->getName() << "\n";
		for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
			errs() << *I << "\n";
		}
	}
	errs() << "\n\n--------------------------------------------------------------------------\n\n\n";
}



///ANOTHER FUNCTIONS

//Return Basic Block position in Basic Block Info Table by id
int GetNumByID(BasicBlock *BB, BasicBlockInfo **table){
	unsigned int i;
	for(i = 0; i < bb_number; i++) if(table[i]->id == BB) return i;
	errs() << "ERROR: GetNumByID failed.\n";
	exit(-1);
}

//Create Basic Block Info Table
void CreateBasicBlockTable(Function &F, BasicBlockInfo **table){
	unsigned int i = 0;
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		table[i] = new BasicBlockInfo();
		table[i]->id = BB;
		table[i]->list = NULL;
		i++;
	}
}