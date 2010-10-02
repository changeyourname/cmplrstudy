//      list.h
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


#ifndef LIST_H
#define LIST_H

#pragma once
#include "elem.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
  
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

#endif /* LIST_H */ 
