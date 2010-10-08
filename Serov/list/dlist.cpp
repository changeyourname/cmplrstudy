#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

struct element
{
    string  value;
    element* next;
    element* prev;
};

//element* mass [6]={};
//int i = 0;
struct dlist
{
private:
    element* fst;
    element* lst;
    element* cur;
public:
    void constructlist ();
    bool ifempty ();
    void addel (string val);
    void curfst ();
    void curlst ();
    void left ();
    void right ();
    void edit (string val);
    void printlist ();
    element* getfst ();
    element* getlst ();
    element* getcur ();
    void delel ();
    void destructlist ();
};

void dlist::constructlist ()
{
    fst = lst = cur = 0;
};

bool dlist::ifempty ()
{
	return (fst == 0);
};

void dlist::addel (string val)
{
	element* el = new element();
	//mass[i] = el;
    el->value = val;
	el->next = NULL;
	if (ifempty () )
	{
		fst = el;
		el->prev = NULL;
	}
	else
	{
        el->prev = lst;
        element* pel = lst;
		pel->next = el;
	}
	lst = el;
	return;
}

void dlist::curfst()
{
    cur = fst;
}

void dlist::curlst()
{
    cur = lst;
}

void dlist::left ()
{
    assert (cur != 0);
    cur = cur->prev;
}

void dlist::right ()
{
    assert (cur !=0 );
    cur = cur->next;
}

void dlist::edit (string val)
{
    assert (cur != 0);
    cur->value = val;
}

void dlist::printlist ()
{
    curfst ();
    cout<<"\nThe elements are:\n";
    while (cur != 0)
    {
        cout << cur->value << "\n";
        right();
    }
    cout << "\n";
    cur = lst;
}

element* dlist::getlst()
{
    return lst;
}

element* dlist::getfst()
{
    return fst;
}

element* dlist::getcur()
{
    return cur;
}

void dlist::delel ()
{
    assert (cur != 0);
    element* pcur = cur->prev;
    element* ncur = cur->next;
    if (fst == lst)
    {
        fst = lst = 0;
        delete (cur);
        cur = 0;
    }

    else
    if (cur == lst)
    {
        lst = pcur;
        pcur->next = 0;
        delete (cur);
        cur = pcur;
    }
    else
    if (cur == fst)
    {
        fst = ncur;
        ncur->prev = 0;
        delete (cur);
        cur = ncur;
    }
    else
    {
        pcur->next = cur->next;
        ncur->prev = cur->prev;
        delete (cur);
        cur = pcur;
	}

}

void dlist::destructlist()
{
    if (!(ifempty ()))
    {
        cur = lst;
        while (cur != 0)
            delel();
    }
}


int main()
{
    int nmax = 0;
    int i = 1;
    string value = "";
    dlist spisok;

    cout << "Enter the number of elemets\n";
    cin >> nmax ;
    cout << "\n";

    spisok.constructlist ();
    cout << "Please, input the elements.\n";
    for (; i <= nmax; i++)
    {
        cin >> value;
        spisok.addel (value);
    }
    spisok.printlist();

   /* spisok.left();
    spisok.left();
    spisok.delel();
    spisok.edit("matrix");
    cout <<"\nThe index is " << spisok.getcur()<< "\n";
    spisok.printlist();
   */

    spisok.destructlist();

    if (spisok.ifempty() != 0)
        cout<<"The list was succsessfully destroyed! \n";
    else
        cout<<"Error! The list wasn't destroyed! \n";
    return 0;
}
