#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>

int
main () {
	list *l = new list;
	int ind;
	while (1) {
		printf ("1. Add to list\n2. Delete elem\n3. Print list\n4. Exit\n");
		scanf ("%d", &ind);
		switch (ind) {
			case 1: {
				int val;
				printf ("Enter value:\n");
				scanf ("%d", &val);
				l->add_elem (val);
			};
			break;
			case 2: {
				int val;
				printf ("Enter value:\n");
				scanf ("%d", &val);
				l->delete_elem (val);
			};
			break;
			case 3: {
				l->print ();
			};
			break;
			case 4: {
				delete l;
				return 0;
			};
		}
	}
}
