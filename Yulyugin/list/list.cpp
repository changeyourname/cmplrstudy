#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>


////////////////////////////////////////////////////////////////////////
elem::~elem (void) {
	if (prev == 0) next->prev = 0;
	else {
		if (next == 0) prev->next = 0;
		else {
			prev->next = next;
			next->prev = prev;
		}
	}
}
////////////////////////////////////////////////////////////////////////
elem::elem (int val) {
	next = NULL;
	prev = NULL;
	value = val;
}
////////////////////////////////////////////////////////////////////////
list::~list (void) {
	if(n != 0) {
		elem *e;
		e = first->next;
		for (int i = 0; i < n-1; i++) {
			delete e->prev;
			e = e->next;
		}
		delete e;
	}
}
////////////////////////////////////////////////////////////////////////
list::list() {
	first = last = 0;
	n = 0;
}
////////////////////////////////////////////////////////////////////////
elem *list::find_elem (int val) {
	if (n == 0) printf ("There isn't any elements in the list\n");
	else {
		elem *e;
		e = first;
		for (int i = 0; i < n; i++) {
			if (e->value != val) e = e->next;
			else return e;
		}
		printf ("There isn't elements with this value in the list\n");
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////
void list::add_elem (int val) {
	if (n == 0) {
		first = last = new elem(val);
		n++;
	}
	else {
		elem *e;
		int ind;
		int var;
		printf ("	1. Add after some element\n	2. Add before some element\n	3. Add in tail\n	4. Add in head\n	");
		scanf ("%d", &ind);
		switch (ind) {
			case 1: {
				printf ("	Enter value of element after which you want to insert:\n	");
				scanf ("%d", &var);
				e = find_elem (var);
				if (e != 0) {
					elem *r = new elem (val);
					if (e == last) {
						last = r;
						e->next = r;
						n++;
					}
					else {
						e->next->prev = r;
						r->next = e->next;
						r->prev = e;
						e->next = r;
						r->prev = e;
						n++;
					}
				}
			};
			break;
			case 2: {
				printf ("	Enter value of element before which you want to insert:\n	");
				scanf ("%d", &var);
				e = find_elem (var);
				if (e != 0) {
					elem *r = new elem (val);
					if (e == first) {
						first = r;
						e->prev = r;
						r->next = e;
						n++;
					}
					else {
						e->prev->next = r;
						r->prev = e->prev;
						r->next = e;
						e->prev = r;
						n++;
					}
				}
			};
			break;
			case 3: {
				e = last;
				elem *r = new elem (val);
				last = r;
				e->next = r;
				r->prev = e;
				n++;
			};
			break;
			case 4: {
				e = first;
				elem *r = new elem (val);
				first = r;
				e->prev = r;
				r->next = e;
				n++;
			};
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////
void list::print (void) {
	elem *e;
	e = first;
	for (int i = 0; i < n; i++) {
		printf ("%d ", e->value);
		printf ("-> ");
		e = e->next;
	}
	printf ("\n");
}
////////////////////////////////////////////////////////////////////////
void list::delete_elem (int val) {
	elem *e;
	e = find_elem (val);
	if (e != 0) {
		if(e == first) {
			first = e->next;
			first->prev = 0;
			n--;
			delete e;
		}
		else {
			if (e == last) {
				last = e->prev;
				last->next = 0;
				n--;
				delete e;
			}
			else {
				e->next->prev = e->prev;
				e->prev->next = e->next;
				n--;
				delete e;
			}
		}
	}
}
