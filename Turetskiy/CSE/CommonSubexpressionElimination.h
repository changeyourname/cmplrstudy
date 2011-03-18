#pragma once


#include <set>
#include <assert.h>
#include <string>
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Analysis/ProfileInfo.h"
#include "llvm/Constant.h"
#include "llvm/Function.h"
#include "llvm/Instruction.h"
#include "llvm/Pass.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Value.h"
#include "List.h"


using namespace llvm;


struct Data{
	unsigned int opcode, num;
	Instruction *I;
	Value *operands[5];
};


struct Var{
	Value *res, *arg;
};


struct Del{
	Instruction *I;
};


unsigned int binary, load;


Data* GetInfo(Instruction *I);
void BinaryProcessing(Data *data, List *del,  List *list, List *var);
void DeadInstructionElimination(List *del);
void DeadValueReplacement(Data *data, List *var);
void LoadProcessing(Data *data, List *del,  List *list, List * var);
void Print(Data *data);
void StoreProcessing(Data *data, List *list, List *var);


Data* GetInfo(Instruction *I){
	unsigned int i;
	Data *data = new Data();
	data->I = I;
	data->opcode = I->getOpcode();
	data->num = I->getNumOperands();
	for(i = 0; i < data->num; i++){
		data->operands[i] = I->getOperand(i);
	}
	return data;
}


void BinaryProcessing(Data *data, List *del,  List *list, List *var){
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
		node = list->GetNext(node);
	}
	if(flag == false) list->AddToEnd(data);
}


void DeadInstructionElimination(List *del){
	Node *node = del->GetFirst();
	while(node != 0){
		Del *d = (Del*) node->data;
		d->I->eraseFromParent();
		node = del->GetNext(node);
	}
}


void DeadValueReplacement(Data *data, List *var){
	unsigned int i;
	Node *node = var->GetFirst();
	while(node != 0){
		Var *v = (Var*) node->data;
		for(i = 0; i < 2; i++){
			if(data->operands[i] == v->res){
				data->I->setOperand(i, v->arg);
				data->operands[i] = v->arg;
			}
		}
		node = var->GetNext(node);
	}
}


void LoadProcessing(Data *data, List *del,  List *list, List * var){
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
		node = list->GetNext(node);
	}
	if(flag == false) list->AddToEnd(data);
}


void Print(Data *data){
	DEBUG(errs() << " \t" << data->I->getName());
	DEBUG(errs() << " \t" << data->I->getOpcodeName());
	for(unsigned int i = 0; i < data->num; i++){
		DEBUG(errs() << " \t" << data->operands[i]->getName());
	}
	DEBUG(errs() << "\n");
}


void StoreProcessing(Data *data, List *list, List *var){
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
		if(flag == false) node = list->GetNext(node);
	}
	delete data;
}