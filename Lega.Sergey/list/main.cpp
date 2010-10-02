#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

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
