#pragma once

#include <assert.h>
#include <iostream>

struct Data{
    //User's information
};


struct Node{
        Data data;
        Node *next, *prev;
};


class List{
    private:
        Node *start, *end;

    public:
        List();
        ~List();

        Data getData(Node *node);
        Node* getFirst();   //Get first Node in List
        Node* getLast();    //Get last Node in List
        void addAfter(Data data, Node *node);   //Add after Node
        void addBefore(Data data, Node *node);  //Add before Node
        void addToEnd(Data data);   //Add to end of List
        void addToStart(Data data); //Add to start of List
        void delFirst();    //Delete first Node in List
        void delLast();     //Delete last Node in List
        void delNode(Node *node);   //Delete Node
        void rndBack();     //Round from end to start of List
        void rndForward();  //Round from start to end of List
};

List::List(){
    start = NULL;
    end = NULL;
}

List::~List(){
    Node *n = start;
    while(n != 0){
        if(n->next == 0){
            delete(n);
            break;
        }
        else{
            n = n->next;
            delete(n->prev);
        }
    }
}

Data List::getData(Node *node){
    assert(node != 0);
    return node->data;
}

Node* List::getFirst(){
    return start;
}

Node* List::getLast(){
    return end;
}

void List::addAfter(Data data, Node *node){
    assert(node != 0);
    Node *n = new Node();
    n->data = data;
    if(node->next == 0){
        addToEnd(data);
    }
    else{
        n->prev = node;
        n->next = node->next;
        node->next->prev = n;
        node->next = n;
    }
}

void List::addBefore(Data data, Node *node){
    assert(node != 0);
    Node *n = new Node();
    n->data = data;
    if(node->prev == 0){
        addToStart(data);
    }
    else{
        n->next = node;
        n->prev = node->prev;
        node->prev->next = n;
        node->prev = n;
    }
}

void List::addToEnd(Data data){
    Node *n = new Node;
    n->data = data;
    n->next = NULL;
    n->prev = end;
    if(end != 0) end->next = n;
    end = n;
    if(start == 0) start = n;
}

void List::addToStart(Data data){
    Node *n = new Node();
    n->data = data;
    n->prev = NULL;
    n->next = start;
    if(start != 0) start->prev = n;
    start = n;
    if(end == 0) end = n;
}

void List::delFirst(){
    assert(start != 0);
    if(start->next == 0){
        delete(start);
        start = NULL;
        end = NULL;
    }
    else{
        start = start->next;
        delete(start->prev);
        start->prev = NULL;
    }
}

void List::delLast(){
    assert(end != 0);
    if(end->prev == 0){
        delete(end);
        start = NULL;
        end = NULL;
    }
    else{
        end = end->prev;
        delete(end->next);
        end->next = NULL;
    }
}

void List::delNode(Node *node){
    assert(node != 0);
    if(node->prev == 0){
        delFirst();
        return;
    }
    if(node->next == 0){
        delLast();
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete(node);
}

void List::rndBack(){
    assert(end != 0);
    Node *n = end;
    while(n != 0){
        //TODO
        n = n->prev;
    }
}

void List::rndForward(){
    assert(start != 0);
    Node *n = start;
    while(n != 0){
        //TODO
        n = n->next;
    }
}
