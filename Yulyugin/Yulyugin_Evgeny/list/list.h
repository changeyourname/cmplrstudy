#ifndef LIST_H
#define LIST_H

class elem {
	elem *prev;
	elem *next;
	int value;
	elem (void);
	elem (int val);
	~elem (void);
	friend class list;
};
////////////////////////////////////////////////////////////////////////
class list {
	elem *find_elem (int val);
	int n;
	elem *first;
	elem *last;
public:
	list (void);
	~list (void);
	void add_elem (int val);
	void delete_elem (int val);
	void print (void);
};

#endif /* LIST_H */
