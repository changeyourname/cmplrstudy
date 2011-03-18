#include <iostream>
#include <assert.h>
#include "list.h"

using namespace std;


struct Data{
    //Something
};


int main(){
    Data *data = new Data();
    List *list = new List();
    Node *node;
    list->AddToStart(data);
    list->AddToEnd(data);
    list->AddToEnd(data);
    node = list->GetLast();
    list->AddToEnd(data);
    list->AddBefore(data, node);
    data = (Data*) list->GetData(node->next);
    delete(list);
    return 0;
}
