#pragma once



///DATA TYPES

struct Node{
        void *data;
        struct Node *next, *prev;
};


class List{
    private:
        Node *start, *end;

    public:
        List();
        ~List();

		bool IsEmpty();
        Node* GetFirst();
		Node* GetLast();
        void AddToEnd(void *data);
        void AddToStart(void *data);
		void ClrFirst();
		void ClrLast();
		void ClrNode(Node *node);
        void DelFirst();
        void DelLast();
        void DelNode(Node *node);
};



///LIST FUNCTION'S DEFINITIONS

List::List(){
    start = 0;
    end = 0;
}


List::~List(){
    Node *n = start;
    while(n != 0){
        if(n->next == 0){
			delete(n->data);
            delete(n);
            break;
        }
        else{
            n = n->next;
			delete(n->prev->data);
            delete(n->prev);
        }
    }
}

//Is List empty or not? 
bool List::IsEmpty(){
	if(end == 0 || start == 0) return true;
	else return false;
}

//Get first Node in List
Node* List::GetFirst(){
    return start;
}

//Get last Node in List
Node* List::GetLast(){
    return end;
}

//Add Data to end of List
void List::AddToEnd(void *data){
    Node *n = new Node;
    n->data = data;
    n->next = 0;
    n->prev = end;
	if(end == 0) start = n;
	else end->next = n;
	end = n;
}

//Add Data to start of List
void List::AddToStart(void *data){
    Node *n = new Node();
    n->data = data;
    n->prev = 0;
    n->next = start;
    if(start != 0) start->prev = n;
    start = n;
    if(end == 0) end = n;
}

//Delete first Node in List, but don't delete Node->Data from memory
void List::ClrFirst(){
	assert(start != 0);
    if(start->next == 0){
        delete(start);
        start = 0;
        end = 0;
    }
    else{
        start = start->next;
        delete(start->prev);
        start->prev = 0;
    }
}

//Delete last Node in List, but don't delete Node->Data from memory
void List::ClrLast(){
    assert(end != 0);
    if(end->prev == 0){
        delete(end);
        start = 0;
        end = 0;
    }
    else{
        end = end->prev;
        delete(end->next);
        end->next = 0;
    }
}

//Delete Node in List, but don't delete Node->Data from memory
void List::ClrNode(Node *node){
    assert(node != 0);
    if(node->prev == 0){
        ClrFirst();
        return;
    }
    if(node->next == 0){
        ClrLast();
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete(node);
}

//Delete first Node in List and delete Node->Data from memory
void List::DelFirst(){
    assert(start != 0);
    if(start->next == 0){
		delete(start->data);
        delete(start);
        start = 0;
        end = 0;
    }
    else{
        start = start->next;
		delete(start->prev->data);
        delete(start->prev);
        start->prev = 0;
    }
}

//Delete last Node in List and delete Node->Data from memory
void List::DelLast(){
    assert(end != 0);
    if(end->prev == 0){
		delete(end->data);
        delete(end);
        start = 0;
        end = 0;
    }
    else{
        end = end->prev;
		delete(end->next->data);
        delete(end->next);
        end->next = 0;
    }
}

//Delete Node in List and delete Node->Data from memory
void List::DelNode(Node *node){
    assert(node != 0);
    if(node->prev == 0){
        DelFirst();
        return;
    }
    if(node->next == 0){
        DelLast();
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
	delete(node->data);
    delete(node);
}