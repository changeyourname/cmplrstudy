#pragma once

#include <memory>

//
//	Требования:
//		- создание и удаление элементов
//		- хранение пользовательских данных
//		- обход списка
//

typedef void (__stdcall LLCLEARDATATAG)(void *);

struct LinkListDataTag
{
	unsigned int uSize;		//	Размер этой структуры
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
	LinkListTag * prev;		//	Предыдущий элемент
	LinkListTag * next;		//	Следующий элемент
	
	void * ptrUserData;		//	Пользовательские данные
	
	union {
		int	ptrReserved;		//	Зарезервированное поле, также выравнивает структуру на 16 байт
		void * ptrUserData2;	//	Вторичное поле хранения пользовательских данных
	};
};

class LinkList
{
public:
	LinkList(void);				//	Стандартный конструктор
	LinkList(LinkList &);		//	Конструктор копирования
	~LinkList(void);			//	Деструктор

	LinkList& operator ++ (void);	//	Инкременирование текущего указателя
	LinkList& operator -- (void);	//	Декрементирование текущего указателя

	LinkList& operator = (const LinkList&);	//	Оператор присвоения

	void*	operator [] (unsigned int in);	//	Доступ к произвольному элемнту
	void*	operator * (void * ptrUserData);//	Для доступа к произвольному элементы

	void	insert(unsigned int uPtr, void * ptrUserData);
	void	begin(void);	
	void	end(void);
	void	clear(void);

	unsigned int size(void);	//	Возвращает размер списка в элементах
	unsigned int max_size(void);	//	Возвращаетмаксимальное кол-воэлементов
	unsigned int resize(unsigned int uNewSize);	// Изменяет размер всего списка

	bool	empty(void);		//	В списке есть элементы?

protected:
	LinkListTag * llThat;		//	Указатель на текущий элементсписка
	LinkListTag * llBegin;		//	Указатель на начало списка
	LinkListTag * llEnd;		//	Указатель на конеч списка

	unsigned int uCount;		//	Количество элементов списка
	unsigned int uCurrList;		//	Номер текущего элемента
};

