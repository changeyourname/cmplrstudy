//      list.cpp
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


#include "list.h"
#include "elem.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
    return false;
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

