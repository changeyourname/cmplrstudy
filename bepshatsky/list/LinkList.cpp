#include "LinkList.h"

LinkList::LinkList(void)
{
	this->uCount = 0;
	this->uCurrList = 0;

	this->llBegin =
	this->llEnd =
	this->llThat =  0;
}

LinkList::LinkList(LinkList &ll)
{
}

LinkList::~LinkList(void)
{
}

unsigned int LinkList::resize(unsigned int uNewSize)
{
	return this->uCount;
}

LinkList& LinkList::operator ++ (void)
{
	if (this->uCurrList < this->uCount)
	{
		if (this->uCurrList ^ 1)
			this->llThat = this->llThat->next;
			
		this->uCurrList++;
	}

	return *this;
}

LinkList& LinkList::operator -- (void)
{
	if (this->uCurrList > 0)
	{
		if (this->uCurrList ^ 1)
			this->llThat = this->llThat->prev;

		this->uCurrList--;
	}

	return *this;
}

void* LinkList::operator * (void * ptr)
{
	if (this->uCount)
	{
		if (ptr)
		{
			void * ptrTmp = new char[*(unsigned int*)ptr];

			if (this->uCurrList ^ 1)
				memcpy(this->llThat->ptrUserData, ptr, *(unsigned int*)ptr);
			else
				memcpy(this->llThat->ptrUserData2, ptr, *(unsigned int*)ptr);

			return ptrTmp;
		}
		else
			return this->uCurrList ^ 1 ? this->llThat->ptrUserData : this->llThat->ptrUserData2;
	}
	else
		return 0;
}

bool LinkList::empty(void)
{
	return this->uCurrList ? true : false;
}

unsigned int LinkList::size(void)
{
	return this->uCurrList;
}

unsigned int LinkList::max_size(void)
{
	return this->uCount;
}

void LinkList::clear(void)
{
	unsigned int uActualSize = (this->uCount & 0xfffffffe) >> 1, uSize;
	LinkListTag * tag = this->llBegin;

	for (unsigned int i = 0; i < uActualSize; i++, tag++)
	{
		uSize = *(unsigned int*)tag->ptrUserData;
		memset(tag->ptrUserData, 0, *(unsigned int*)tag->ptrUserData);
		*(unsigned int*)tag->ptrUserData = uSize;

		uSize = *(unsigned int*)tag->ptrUserData2;
		memset(tag->ptrUserData2, 0, *(unsigned int*)tag->ptrUserData2);
		*(unsigned int*)tag->ptrUserData = uSize;
	}

	if (this->uCount & 1)
	{
		uSize = *(unsigned int*)tag->ptrUserData;
		memset(tag->ptrUserData, 0, *(unsigned int*)tag->ptrUserData);
		*(unsigned int*)tag->ptrUserData = uSize;
	}
}

