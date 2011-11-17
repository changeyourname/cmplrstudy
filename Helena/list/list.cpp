#include <iostream>
#include <stdio.h>


struct Node{
	int dat;
	Node *next;
	Node *prev;
};

Node* first(int d);
void add (Node **pend, int d);
Node* find(Node * const pbeg, int i);
bool remove (Node **head, Node **tail, int key);
Node* insert (Node * const head, Node **tail, int key, int d);

/////////////////////////////////////////////////////////////

//create first element
Node* first(int d){
	Node *pv = new Node;
	pv->dat = d;
	pv->next = 0;
	pv->prev = 0;
	return pv;
}
////////////////////////////////////////////////////////////

//add to end of list
void add(Node **pend, int d){
	Node *pv = new Node;
	pv->dat = d;
	pv->next = 0;
	pv->prev = *pend;
	(*pend)->next = pv;
	*pend = pv;
}///////////////////////////////////////////////////////////

//find element by key
Node* find(Node * const pbeg, int d){
	Node *pv = pbeg;
	while (pv){
		if(pv->dat == d)break;
		pv = pv->next;
	}
	return pv;
}
////////////////////////////////////////////////////////////

//delete element
bool remove(Node **pbeg, Node **pend, int key){
	if(Node *pkey = find(*pbeg, key)){
		if(pkey == *pbeg){
			*pbeg = (*pbeg)->next;
			(*pbeg)->prev = 0;}
		else if (pkey == *pend){
			*pend = (*pend)->prev;
			(*pend)->next = 0;}
		else{
			(pkey->prev)->next = pkey->next;
			(pkey->next)->prev = pkey->prev;}
		delete pkey;
		return true;	
	}
	return false;
}
///////////////////////////////////////////////////////////

//insert element
Node* insert(Node * const pbeg, Node **pend, int key, int d){
	if(Node *pkey = find(pbeg,key)){
		Node *pv = new Node;
		pv->dat = d;
		pv->next = pkey->next;
		pv->prev = pkey;
		pkey->next = pv;
		if( pkey != *pend)
			(pv->next)->prev=pv;
		else *pend = pv;
		return pv;
	}
return 0;	
}


int main(){
	Node *pbeg = first(15); //create first element 15 
	Node *pend = pbeg;
	for (int i = 2; i<6; i++) //insret 2 3 4 5 6
		add (&pend, i);
	insert(pbeg, &pend, 3, 600);				//insert 600 after 3
	if(!remove(&pbeg, &pend, 5)) 
		printf("not found"); //delete 5
	Node *pv = pbeg;
	while (pv){			//print list									
		printf("%d ",pv->dat);
		pv = pv->next;
	}
	return 0; 
}
