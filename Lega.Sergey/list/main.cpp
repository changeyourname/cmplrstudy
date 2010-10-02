//      main.cpp
//      
//      Copyright 2010 Lega Sergey <destructor@gravihost>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <string>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class Elem{
  public: 
    Elem *GetPrev(void);
    Elem *GetNext(void);
    const char *GetData(void);
    void SetPrev(Elem *prev);
    void SetNext(Elem *next);
    void SetData(const std::string &data);
    Elem(const std::string &data);
    Elem(void);
    virtual ~Elem(void) {};
    
  private:
    std::string data_;
    Elem *prev_;
    Elem *next_;
    DISALLOW_COPY_AND_ASSIGN(Elem);
};

Elem* Elem::GetPrev(void) {
  return prev_;
};

Elem* Elem::GetNext(void) {
  return next_;
}

const char* Elem::GetData(void) {
  return data_.c_str();
}

void Elem::SetPrev(Elem *prev) {
  prev_ = prev;
}

void Elem::SetNext(Elem *next) {
  next_ = next;
}

void Elem::SetData(const std::string &data) {
  data_ = data.c_str();
}

Elem::Elem(const std::string& data) {
  next_ = NULL;
  prev_ = NULL;
  std::string data_;
  data_ = data.c_str();
}

Elem::Elem(void) {
  next_ = NULL;
  prev_ = NULL;
  data_ = "\0"; 
}

class List{
  public:
    void SetHead(Elem* head);
    void SetTail(Elem* tail);
    void SetCount(int count);
    Elem *GetHead(void);
    Elem *GetTail(void);
    int GetCount(void);
    void InsertToList(const std::string& data);
    bool RemoveFromList(const std::string& data);
    void ListPrint(void);
    void ClearList(void);
    List(void);
    virtual ~List(void);
    
  private:
    void DeleteElements(Elem* el);
    int count_;
    Elem *head_;
    Elem *tail_;
    DISALLOW_COPY_AND_ASSIGN(List);
};

Elem* List::GetHead(void) {
  if (count_) return head_;
  else return NULL;
}

void List::SetTail(Elem* tail) {
  if (tail) {
    tail_ = tail;
  } else {
    fprintf(stderr, "ERR: wrong pointer for SetTail\n");
    exit(EXIT_FAILURE);
  }
}

void List::SetHead(Elem* head) {
  if (head) {
    head_ = head;
  } else {
    fprintf(stderr, "ERR: wrong pointer for SetHead\n");
    exit(EXIT_FAILURE);
  }

}

Elem* List::GetTail(void) {
  if (count_) return tail_;
  else return NULL;
}

List::~List(void) {
  if (count_)
    DeleteElements(GetHead());
}

List::List(void) {
  head_ =NULL;
  count_ = 0;
  tail_ = NULL;
}

void List::InsertToList(const std::string &data){
  Elem *r = NULL;
  try {
    r = new Elem(data);
  }
  catch (...) {
    fprintf(stderr, strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  if(count_ == 0){ 
    SetTail(r);
    SetHead(r);
    r->SetData(data);
  }
  else {
    r->SetData(data);
    r->SetPrev(GetTail());
    r->SetNext(NULL);
    GetTail()->SetNext(r);
    SetTail(r);
  }
  count_++;
} 

void List::DeleteElements(Elem* el) {
  if(el) {
    if(el->GetNext()) {
      DeleteElements(el->GetNext());
    }
  delete el;
  }
}

void List::ClearList() {
  DeleteElements(head_);
  count_ = 0;
}

bool List::RemoveFromList(const std::string &data) {
  if(count_ == 0) {
    return 1;
  }
  Elem *r;
  bool flag = false;
  for(r = tail_; r != NULL; r = r->GetPrev()) {
    if(strcmp(r->GetData(), data.c_str()) == 0) {
        if(r == head_) {
          if(count_ == 1) {
          delete r;
          flag = true;
          head_= NULL;
          count_--;
        }
        else if(count_ != 1) { 
          head_ = r->GetNext();
          r->GetNext()->SetPrev(NULL);
          delete r;
          flag = true;
          count_--;
          }
        }
      else if(r == tail_) {
        if (count_ != 1) {
          tail_ = r->GetPrev();
          r->GetPrev()->SetNext(NULL);
          delete r;
          flag = true;
          count_--;
        }
        else {
          tail_ = NULL;
          head_ = NULL;
          delete r;
          flag = true;
          count_--;
        }
      } 
      else {
      r->GetPrev()->SetNext(r->GetNext());
      r->GetNext()->SetPrev(r->GetPrev());
      delete r;
      flag = true;
      count_--;
        }
      }
    }
  return flag;
}

void List::ListPrint(void) {
  Elem *r;
  try {
    r = new Elem();
  }
  catch(...) {
    fprintf(stderr,"ERR: no memory\n");
    return;
  }
  for(r = head_; r != NULL;r = r->GetNext()) {
    printf("(%s)->\n",r->GetData());
  }
}

int main(int argc, char **argv)
{
  char cmd[1024], *data=NULL;
  List *l;
  
  if(argc != 1) {
    fprintf(stderr, "ERR: wrong number of arguments\n");
    exit(EXIT_FAILURE);
  }
  
  try {
  l=new List();
  }
  catch(...) {
    fprintf(stderr,"ERR: no memory\n");
    exit(EXIT_FAILURE);
  }
  
  data = new char[100];
  
  if(cmd == NULL || data == NULL) {
    fprintf(stderr, "ERR: no memory");
    exit(EXIT_FAILURE);
  }
  
  while (1) {
  
    fgets( cmd, sizeof(cmd), stdin );

    if ( strncmp( cmd, "ADD", 3 ) == 0 ) {
      
      fgets(data, sizeof(char)*100, stdin);
      
      l->InsertToList(data);
      
      memset(data, 0, sizeof(char)*100);
      
    } else if ( strncmp( cmd, "DEL", 3 ) == 0 ) {
      fgets(data, sizeof(char)*100, stdin);
      
      if(l->RemoveFromList(data)) 
        printf("%s\n","Deleted successfuly");
      
      else 
      fprintf(stderr,"ERR: not found");
      
      memset(data, 0, sizeof(char)*100);
    
    } else if ( strncmp( cmd, "PRINT", 5) == 0 ) {
      l->ListPrint();
    
    } else if ( strncmp( cmd, "EXIT", 4) == 0 ) {
      if (l)
        delete l;
      free(data);
      exit(EXIT_SUCCESS);
    
    } else if( strncmp( cmd, "CLEAR LIST", 10) == 0) {
      l->ClearList();
    
    } else {
      printf("%s\n  %s\n  %s\n  %s\n  %s\n  %s\n","Invalid argument. Usage:",
      "ADD- add element","DEL- delete element","PRINT- print list",
      "CLEAR LIST- delete all elements","EXIT- exit");
    }
    
  }
  
  exit(EXIT_SUCCESS);
}
