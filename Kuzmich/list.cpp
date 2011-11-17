#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <new>

using namespace std;

/* Узел списка */
class Node{
  public:
    int data;
    Node *next_link;
    Node *prev_link;
    Node (int data);
    Node (void);
    ~Node (void) {};
};

/* Конструкторы */
Node::Node(int input_data){
  next_link = NULL;
  prev_link = NULL;
  data = input_data;
}

Node::Node(void) {
  next_link = NULL;
  prev_link = NULL;
  data = 0;
}

/* Двусвязный Список */
class List{
  public:
    Node *head;
    Node *tail;
    int lenght;
    void PrintForward(void);
    void PrintBackward(void);
    void AddToList(int input_data);
    int  RemoveFromList(int input_data);
    void DelAll(Node *node);
    void ClearList(void);
    List(void);
    ~List(void);
};

List::List(void){
  head = NULL;
  tail = NULL;
  lenght = 0;
}

List::~List(void){
  DelAll(head);
}

void List::ClearList(void){
  DelAll(head);
  lenght = 0;
}

void List::DelAll(Node *node){
  if(node){
    if(node->next_link)
      DelAll(node->next_link);
    delete node;
  }
}

void List::AddToList(int input_data){

  Node *new_node=new(nothrow) Node(input_data);

  if (lenght){
    new_node->next_link = NULL;
    new_node->prev_link = tail;
    tail->next_link=new_node;
    tail = new_node;
  } else {
    tail = new_node;
    head = new_node;
    new_node->next_link = NULL;
    new_node->prev_link = NULL;
  }
  new_node->data = input_data;
  lenght++;
}

int List::RemoveFromList(int input_data) {
  if (!lenght){
    fprintf(stderr,"Can't remove from list, List is clear");
    return 1;
  }

  Node *victim;
  for (victim = head; victim ; victim = victim->next_link){
    if (input_data == victim->data){
      if (lenght > 1){
        if (victim != head )
          victim->prev_link->next_link = victim->next_link;
        else
          head = victim->next_link;

        if (victim != tail )
          victim->next_link->prev_link = victim->prev_link;
        else
          tail = victim->prev_link;
      } else {
        head = NULL;
        tail = NULL;
      }
      delete victim;
      lenght--;
    }
  }
  return 0;
}

void List::PrintForward(void) {
  if (lenght){
    Node* node = new Node();
    if (node = NULL) {
      fprintf(stderr,"Error ! No memory !\n");
      exit (EXIT_FAILURE);
    }
    for(node = head; node != NULL; node=node->next_link){
      printf("%i\n",node->data);
    }
  } else {
    printf("Can't print! List is empty\n");
  }
}

void List::PrintBackward(void) {
  if (lenght){
    Node* node = new Node();
    if (node = NULL) {
      fprintf(stderr,"Error ! No memory !\n");
      exit (EXIT_FAILURE);
    }
    for(node = tail; node != NULL; node=node->prev_link){
      printf("%i\n",node->data);
    }
  } else {
    printf("Can't print! List is empty\n");
  }
}

int main(){
  /* Пример */
  List *l=new List();
  l->AddToList(100);
  l->AddToList(300);
  l->RemoveFromList(300);
  l->AddToList(400);
  l->PrintBackward();
  l->ClearList();
  l->PrintForward();
  delete l;
  return 0;
}
