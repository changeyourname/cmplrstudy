#include "list.h"

using namespace std;

int main(){
    Data data;
    List *list = new List();
    Node* node;
    list->addToStart(data);
    list->addToEnd(data);
    list->addToEnd(data);
    node = list->getLast();
    list->addToEnd(data);
    list->rndBack();
    list->addBefore(data, node);
    list->rndForward();
    data = list->getData(node->next);
    delete(list);
    return 0;
}
