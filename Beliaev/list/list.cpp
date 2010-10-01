#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

using namespace std;

class node
{
	public:
	node *prev;
	node *next;
	int data;
	node(int data);
	~node(void);
};

class list
{
	public:
	node *tail;
	node *head;
	void list_print(node *h);
	void node_insert(int data);
	int node_remove(int data);
	list(void);
	~list(void);
};

node::node(int data) 
{
	next=0;
	prev=0;
	data=data;
}
list::list(void){
	tail=0;
	head=0;
}

void list::list_print(node *h){
	node *n;
		
		for(n=h;n!=0;n=n->next)
		{printf("%d->",n->data);}
	}

void list::node_insert(int d){
	node *n=new(nothrow) node(d);
	if(n==0) {fprintf(stderr,"no memory fail\n"); exit(EXIT_FAILURE);}
		n->data=d;
		if(head==0) 
		{head=n; tail=n;}
	else
		{tail->next=n;
		n->prev=tail;
		tail=n;
	    }
	}
	
int list::node_remove(int d){
	node *n;
	if(head==0) {fprintf(stderr,"nothing to delete fail\n"); return 1;}
	if(head->data==d)
		{n=head; head=head->next; free(n); return 0;}
	if(tail->data==d)
		{n=tail; tail=tail->prev; free(n); return 0;}
	n=head->next;
	while(n!=tail)
	{if(n==0) {fprintf(stderr,"hole in teh list fail\n"); exit(EXIT_FAILURE);}
	if(n->data==d) {n->prev->next=n->next; free(n); return 0;}
	n=n->next;
	}
	return 0;}	
	
int main(int argc, char *argv[])
	{list *l=new(nothrow) list();
	char cmd[3];
	int dat;
	while(1) {
	scanf("%s",cmd);
	if(strncmp(cmd,"DEL",3)==0)
	{scanf("%d",&dat); l->node_remove(dat);} else
	if(strncmp(cmd,"INS",3)==0)
	{scanf("%d",&dat); l->node_insert(dat);} else
	if(strncmp(cmd,"PRN",3)==0)
	{l->list_print(l->head);} else
	if(strncmp(cmd,"EXT",3)==0)
	{return 0;} else
	printf("wrong input. PRN to print teh list, INS to insert, DEL to remove somethin, EXT to exit\n");
	}
	
	return 0;
	}
