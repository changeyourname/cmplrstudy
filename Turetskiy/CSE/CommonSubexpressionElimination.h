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


struct BasicBlockInfo{
	BasicBlock *id;
	List *list;
};


struct Data{
	unsigned int opcode, num;
	Instruction *I;
	Value *operands[32];
};


struct Var{
	Value *res, *arg;
};


struct Del{
	Instruction *I;
};


unsigned int bb_number, binary, load;


//List functions
bool ListComparison(List *list1, List *list2);
List* ListIntersection(List *list1, List *list2);
void ListCopy(List *src, List *dst);

//Local CSE functions
void LocalCSE(BasicBlock *BB, List *list_input);
void DeadInstructionElimination(List *del);
void DeadValueReplacement(Data *data, List *var);
void ProcessingBinary(Data *data, List *del,  List *list, List *var);
void ProcessingLoad(Data *data, List *del,  List *list, List * var);
void ProcessingStore(Data *data, List *list, List *var);

//Make BasicBlock List functions
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




//LIST FUNCTIONS------------------------------------------------------------------------------------------------------


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


List* ListIntersection(List *list1, List *list2){
	List *intersection = new List();
	Data *data1, *data2;
	Node *node1, *node2;
	unsigned int i;
	for(node1 = list1->GetFirst(); node1 != 0; node1 = node1->next){
		data1 = (Data*) node1->data;
		for(node2 = list2->GetFirst(); node2 != 0; node2 = node2->next){
			data2 = (Data*) node2->data;
			if(data1->I == data2->I){
				Data *data = new Data();
				data->I = data1->I;
				data->num = data1->num;
				data->opcode = data1->opcode;
				for(i = 0; i < data->num; i++) data->operands[i] = data1->operands[i];
				intersection->AddToEnd(data);
				break;
			}
		}
	}
	return intersection;
}


void ListCopy(List *src, List *dst){
	Node *node;
	unsigned int i;
	for(node = src->GetFirst(); node != 0; node = node->next){
		Data *data_dst = new Data();
		Data *data_src = (Data*) node->data;
		data_dst->I = data_src->I;
		data_dst->num = data_src->num;
		data_dst->opcode = data_src->opcode;
		for(i = 0; i < data_dst->num; i++) data_dst->operands[i] = data_src->operands[i];
		dst->AddToEnd(data_dst);
	}
}


//LOCAL CSE FUNCTIONS--------------------------------------------------------------------------------------------------


void LocalCSE(BasicBlock *BB, List *list_input){
	List *del = new List();
	List *var = new List();
	for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
		Data *data = GetInfo(I);
		if(data->opcode >= 8 && data->opcode <= 25) ProcessingBinary(data, del, list_input, var);
		else if(data->opcode == 27) ProcessingLoad(data, del, list_input, var);
		else if(data->opcode == 28) ProcessingStore(data, list_input, var);
		else{
			DeadValueReplacement(data, var);
			delete data;
		}
	}
	DeadInstructionElimination(del);
	delete del;
	delete list_input;
	delete var;
}


void DeadInstructionElimination(List *del){
	Node *node = del->GetFirst();
	while(node != 0){
		Del *d = (Del*) node->data;
		d->I->eraseFromParent();
		node = node->next;
	}
}


void DeadValueReplacement(Data *data, List *var){
	unsigned int i;
	Node *node = var->GetFirst();
	while(node != 0){
		Var *v = (Var*) node->data;
		for(i = 0; i < data->num; i++){
			if(data->operands[i] == v->res){
				data->I->setOperand(i, v->arg);
				data->operands[i] = v->arg;
			}
		}
		node = node->next;
	}
}


void ProcessingBinary(Data *data, List *del,  List *list, List *var){
	bool flag = false;
	DeadValueReplacement(data, var);
	Node *node = list->GetFirst();
	while(node != 0){
		Data *dt = (Data*) node->data;
		if(data->opcode == dt->opcode){
			if(data->operands[0] == dt->operands[0] && data->operands[1] == dt->operands[1]){
				Del *d = new Del();
				Var *v = new Var();
				d->I = data->I;
				v->res = data->I;
				v->arg = dt->I;
				del->AddToEnd(d);
				var->AddToEnd(v);
				binary++;
				flag = true;
			}
			if(data->opcode == 8 || data->opcode == 9 || data->opcode == 12 || data->opcode == 13 || data->opcode == 23 || data->opcode == 24 || data->opcode == 25){
				if(data->operands[0] == dt->operands[1] && data->operands[1] == dt->operands[0]){
					Del *d = new Del();
					Var *v = new Var();
					d->I = data->I;
					v->res = data->I;
					v->arg = dt->I;
					del->AddToEnd(d);
					var->AddToEnd(v);
					binary++;
					flag = true;
				}
			}
		}
		node = node->next;
	}
	if(flag == false) list->AddToEnd(data);
}


void ProcessingLoad(Data *data, List *del,  List *list, List * var){
	bool flag = false;
	Node *node = list->GetFirst();
	while(node != 0){
		Data *dt = (Data*) node->data;
		if(dt->opcode == 27){
			if(dt->operands[0] == data->operands[0]){
				Del *d = new Del();
				Var *v = new Var();
				d->I = data->I;
				v->res = data->I;
				v->arg = dt->I;
				del->AddToEnd(d);
				var->AddToEnd(v);
				load++;
				flag = true;
				break;
			}
		}
		node = node->next;
	}
	if(flag == false) list->AddToEnd(data);
}


void ProcessingStore(Data *data, List *list, List *var){
	unsigned int i;
	DeadValueReplacement(data, var);
	Node *node = list->GetFirst();
	while(node != 0){
		bool flag = false;
		Data *d = (Data*) node->data;
		for(i = 0; i < d->num; i++){
			if(d->operands[i] == data->operands[1]){
				Node *n = node->next;
				list->DelNode(node);
				node = n;
				flag = true;
				break;
			}
		}
		if(flag == false) node = node->next;
	}
	delete data;
}


//MAKE LIST FUNCTIONS-------------------------------------------------------------------------------------------------


void MakeAllInputLists(BasicBlockInfo **table){
	List *queue = new List();

	List *entry_list = new List();
	table[0]->list = entry_list;
	queue->AddToEnd(table[0]);

	while(queue->IsEmpty() == false){
		BasicBlockInfo *BBI = (BasicBlockInfo*) queue->GetFirst()->data;
		queue->ClrFirst();
		List *list_out = new List();
		ListCopy(BBI->list, list_out);

		MakeListOut(BBI->id, BBI->list, list_out);

		DEBUG(errs() << BBI->id->getName() << "\n"; PrintDataList(BBI->list); errs() << "\n"; PrintDataList(list_out); errs() << "---\n";);

		for(succ_iterator SUCC = succ_begin(BBI->id); SUCC != succ_end(BBI->id); SUCC++){
			BasicBlockInfo *info = table[GetNumByID(*SUCC, table)];
			if(info->list == NULL){
				List *list = new List();
				ListCopy(list_out, list);
				info->list = list;
				queue->AddToEnd(info);
			}
			else{
				List *intersection = ListIntersection(list_out, info->list);
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


void MakeListOut(BasicBlock *BB, List *list_in, List *list_out){
	for(BasicBlock::iterator I = BB->begin(); I != BB->end(); I++){
		Data *data = GetInfo(I);
		if(data->opcode >= 8 && data->opcode <= 25) MakeBinary(data, list_out);
		else if(data->opcode == 27) MakeLoad(data, list_out);
		else if(data->opcode == 28) MakeStore(data, list_out);
		else delete data;
	}
}


void MakeBinary(Data *data, List *list){
	bool flag = false;
	Node *node = list->GetFirst();
	while(node != 0){
		Data *dt = (Data*) node->data;
		if(data->opcode == dt->opcode){
			if(data->operands[0] == dt->operands[0] && data->operands[1] == dt->operands[1]){
				flag = true;
				break;
			}
			if(data->opcode == 8 || data->opcode == 9 || data->opcode == 12 || data->opcode == 13 || data->opcode == 23 || data->opcode == 24 || data->opcode == 25){
				if(data->operands[0] == dt->operands[1] && data->operands[1] == dt->operands[0]){
					flag = true;
					break;
				}
			}
		}
		node = node->next;
	}
	if(flag == false) list->AddToEnd(data);
}


void MakeLoad(Data *data, List *list){
	bool flag = false;
	Node *node = list->GetFirst();
	while(node != 0){
		Data *dt = (Data*) node->data;
		if(dt->opcode == 27){
			if(dt->operands[0] == data->operands[0]){
				flag = true;
				break;
			}
		}
		node = node->next;
	}
	if(flag == false) list->AddToEnd(data);
}


void MakeStore(Data *data, List *list){
	unsigned int i;
	Node *node = list->GetFirst();
	while(node != 0){
		bool flag = false;
		Data *d = (Data*) node->data;
		for(i = 0; i < d->num; i++){
			if(d->operands[i] == data->operands[1]){
				Node *n = node->next;
				list->DelNode(node);
				node = n;
				flag = true;
				break;
			}
		}
		if(flag == false) node = node->next;
	}
	delete data;
}



//PRINT FUNCTIONS-----------------------------------------------------------------------------------------------------


void PrintDataList(List *list){
	Node *node;
	for(node = list->GetFirst(); node != 0; node = node->next){
		Data *data = (Data*) node->data;
		errs() << *(data->I) << "\n";
	}
}


void PrintDelList(List *list){
	Node *node;
	for(node = list->GetFirst(); node != 0; node = node->next){
		Del *del = (Del*) node->data;
		errs() << *(del->I) << "\n";
	}
}


void PrintVarList(List *list){
	Node *node;
	for(node = list->GetFirst(); node != 0; node = node->next){
		Var *var = (Var*) node->data;
		errs() << var->arg->getName() << " = " << var->res->getName() << "\n";
	}
}


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


//ANOTHER FUNCTIONS------------------------------------------------------------------------------------------------------


Data* GetInfo(Instruction *I){
	unsigned int i;
	Data *data = new Data();
	data->I = I;
	data->opcode = I->getOpcode();
	data->num = I->getNumOperands();
	for(i = 0; i < data->num; i++) data->operands[i] = I->getOperand(i);
	return data;
}


int GetNumByID(BasicBlock *BB, BasicBlockInfo **table){
	unsigned int i;
	for(i = 0; i < bb_number; i++) if(table[i]->id == BB) return i;
	errs() << "ERROR: GetNumByID failed.\n";
	exit(-1);
}


void CreateBasicBlockTable(Function &F, BasicBlockInfo **table){
	unsigned int i = 0;
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++){
		table[i] = new BasicBlockInfo();
		table[i]->id = BB;
		table[i]->list = NULL;
		i++;
	}
}

