#pragma once


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

        void* GetData(Node *node);					//Get data
        Node* GetFirst();							//Get first Node in List
		Node* GetLast();							//Get last Node in List
		Node* GetNext(Node* node);					//Get next Node
		Node* GetPrev(Node* node);					//Get previous Node
        void AddAfter(void *data, Node *node);		//Add after Node
        void AddBefore(void *data, Node *node);		//Add before Node
        void AddToEnd(void *data);					//Add to end of List
        void AddToStart(void *data);				//Add to start of List
        void DelFirst();							//Delete first Node in List
        void DelLast();								//Delete last Node in List
        void DelNode(Node *node);					//Delete Node
};

List::List(){
    start = NULL;
    end = NULL;
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

void* List::GetData(Node *node){
    assert(node != 0);
    return node->data;
}

Node* List::GetFirst(){
    return start;
}

Node* List::GetLast(){
    return end;
}

Node* List::GetNext(Node *node){
	if(node == 0) return 0;
	return node->next;
}

Node* List::GetPrev(Node *node){
	if(node == 0) return 0;
	return node->prev;
}

void List::AddAfter(void *data, Node *node){
    assert(node != 0);
    Node *n = new Node();
    n->data = data;
    if(node->next == 0){
        AddToEnd(data);
    }
    else{
        n->prev = node;
        n->next = node->next;
        node->next->prev = n;
        node->next = n;
    }
}

void List::AddBefore(void *data, Node *node){
    assert(node != 0);
    Node *n = new Node();
    n->data = data;
    if(node->prev == 0){
        AddToStart(data);
    }
    else{
        n->next = node;
        n->prev = node->prev;
        node->prev->next = n;
        node->prev = n;
    }
}

void List::AddToEnd(void *data){
    Node *n = new Node;
    n->data = data;
    n->next = NULL;
    n->prev = end;
	if(end == 0) start = n;
	else{
		assert(end != 0);
		end->next = n;
	}
	end = n;
}

void List::AddToStart(void *data){
    Node *n = new Node();
    n->data = data;
    n->prev = NULL;
    n->next = start;
    if(start != 0) start->prev = n;
    start = n;
    if(end == 0) end = n;
}

void List::DelFirst(){
    assert(start != 0);
    if(start->next == 0){
		delete(start->data);
        delete(start);
        start = NULL;
        end = NULL;
    }
    else{
        start = start->next;
		delete(start->prev->data);
        delete(start->prev);
        start->prev = NULL;
    }
}

void List::DelLast(){
    assert(end != 0);
    if(end->prev == 0){
		delete(end->data);
        delete(end);
        start = NULL;
        end = NULL;
    }
    else{
        end = end->prev;
		delete(end->next->data);
        delete(end->next);
        end->next = NULL;
    }
}

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