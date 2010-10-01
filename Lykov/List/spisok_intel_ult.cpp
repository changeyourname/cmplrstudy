#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

struct dllist 
{
 int number;
 dllist *next;
 dllist *prev;
};

dllist *head;
dllist *tail;


// adding node
void add_node(dllist *lnode) 
{
 if(head == NULL) 
	{
		head = lnode;
		lnode->prev = NULL;
	} 
 else 
	{
		tail->next = lnode;
		lnode->prev = tail;
	}
 tail = lnode;
 lnode->next = NULL;
}


//insert node
dllist *insert_node(dllist *pos, int num)
{
	dllist *new_rec, *tmp_rec, *prev_rec;
	new_rec = new dllist;		
	new_rec->number = num; 

	if(head == 0)
	{
		head = new_rec;
	}
	else
	{
		tmp_rec = pos->next;
		prev_rec = pos;
		prev_rec->next = new_rec;
		new_rec->next = tmp_rec;
	}
	cout << "node was inserted to the list number = " << new_rec->number << "\n";
	return new_rec;
}

//remove node
void remove_node(dllist *lnode) 
{
	if(lnode->prev == NULL)
		head = lnode->next;
	else
		lnode->prev->next = lnode->next;
	if(lnode->next == NULL)
		tail = lnode->prev;
	else
		lnode->next->prev = lnode->prev;
	cout << "node was removed(addres): " << lnode << " with data: " << lnode->number << "\n";
	delete lnode;
}


//show list
void show_list()
{
	dllist *cur_ptr;
	cur_ptr = head;
	cout << "---------SHOW_LIST-----------\n";
	while (cur_ptr != NULL)
	{
		cout << "node data = " << cur_ptr->number << "\n";
		cur_ptr = cur_ptr->next;
	}
	cout << "-----------------------------\n";
}


// find person
dllist *find_person(int number)
{
	dllist *cur_ptr; 
	cur_ptr = head;	
	while (cur_ptr != NULL)
	{
		if(cur_ptr->number == number)
			break;
		cur_ptr = cur_ptr->next;
	}
	cout << "number found: " << cur_ptr->number << "\n";
	return cur_ptr;
}



int main()
{
	dllist *lnode;
	int i = 0;

	head = NULL;

	for(i = 0; i <= 5; i++) 
	{
		lnode = new dllist;
		lnode->number = i;
		add_node(lnode);
	}

	show_list();

	lnode = find_person(2);
	insert_node(head,11);
	
	remove_node(tail);
	remove_node(head);
	
	show_list();
	system("pause");	
	return 0;
}
