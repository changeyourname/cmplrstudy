#pragma once

#include <memory>

//
//	����������:
//		- �������� � �������� ���������
//		- �������� ���������������� ������
//		- ����� ������
//

typedef void (__stdcall LLCLEARDATATAG)(void *);

struct LinkListDataTag
{
	unsigned int uSize;		//	������ ���� ���������
};

struct LinkListDataUINTx1
{
	unsigned int uSize;

	unsigned int uNumb;
};

struct LinkListDataUINTx3
{
	unsigned int uSize;

	unsigned int uNumb1;
	unsigned int uNumb2;
	unsigned int uNumb3;
};

struct LinkListTag
{
	LinkListTag * prev;		//	���������� �������
	LinkListTag * next;		//	��������� �������
	
	void * ptrUserData;		//	���������������� ������
	
	union {
		int	ptrReserved;		//	����������������� ����, ����� ����������� ��������� �� 16 ����
		void * ptrUserData2;	//	��������� ���� �������� ���������������� ������
	};
};

class LinkList
{
public:
	LinkList(void);				//	����������� �����������
	LinkList(LinkList &);		//	����������� �����������
	~LinkList(void);			//	����������

	LinkList& operator ++ (void);	//	���������������� �������� ���������
	LinkList& operator -- (void);	//	����������������� �������� ���������

	LinkList& operator = (const LinkList&);	//	�������� ����������

	void*	operator [] (unsigned int in);	//	������ � ������������� �������
	void*	operator * (void * ptrUserData);//	��� ������� � ������������� ��������

	void	insert(unsigned int uPtr, void * ptrUserData);
	void	begin(void);	
	void	end(void);
	void	clear(void);

	unsigned int size(void);	//	���������� ������ ������ � ���������
	unsigned int max_size(void);	//	���������������������� ���-�����������
	unsigned int resize(unsigned int uNewSize);	// �������� ������ ����� ������

	bool	empty(void);		//	� ������ ���� ��������?

protected:
	LinkListTag * llThat;		//	��������� �� ������� �������������
	LinkListTag * llBegin;		//	��������� �� ������ ������
	LinkListTag * llEnd;		//	��������� �� ����� ������

	unsigned int uCount;		//	���������� ��������� ������
	unsigned int uCurrList;		//	����� �������� ��������
};

