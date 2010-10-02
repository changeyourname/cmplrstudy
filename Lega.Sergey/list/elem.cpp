//      elem.cpp
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


#include "elem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
