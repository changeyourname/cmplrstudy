//      elem.h
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


#ifndef ELEM_H
#define ELEM_H

#pragma once
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

#endif /* ELEM_H */ 
