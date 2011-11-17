/*
 * ocheredilibs.c
 * Encoding is UTF-8, author from Russia and use russian dictionary
 *  Created on: 14.12.2009
 *      Author: Morgen Matvey MIPT
 *				Group 914 Room 432a
 */
#include "ocheredilibs.h"

//Создаём очередь
truba_t* create_truba(){
	truba_t *truba = (truba_t*)malloc(sizeof(truba_t));
	truba->head = NULL;
	truba->last = NULL;
	return truba;
}

//Деструктор очереди
void destroy_truba(truba_t *truba){
	ochered_t *next, *elem = truba->head;
	while(elem){
		next = elem->next;
		free(elem);
		elem = next;
	}
	free(truba);
}

//Вставка элемента в начало
void addhead_truba(truba_t *truba, int a){
	ochered_t *elem = (ochered_t*)malloc(sizeof(ochered_t));
	elem->value = a;
	elem->gonext = 0;
	elem->next = truba->head;
	if(!(truba->last)){
		truba->last = elem;
	}
	if(truba->head){
		truba->head->prev = elem;
	}
	elem->prev = NULL;
	truba->head = elem;
}

//Вставка элемента в конец
void addlast_truba(truba_t *truba, int a){
	ochered_t *elem = (ochered_t*)malloc(sizeof(ochered_t));
	elem->value = a;
	elem->gonext = 0;
	elem->prev = truba->last;
	if(!(truba->head)){
		truba->head = elem;
	}
	if(truba->last){
		truba->last->next = elem;
	}
	elem->next = NULL;
	truba->last = elem;
}

//Удаление элементов содержащих а
int remove_truba(truba_t *truba, int a){
	ochered_t *next, *elem = truba->head;
	if(!elem){
		fprintf(stderr,"Segmentation fault, Stack is empty!\n");
		return 0;
	}
	while(elem){
		if(elem->value == a){
			if(elem->prev){
				elem->prev->next= elem->next;
			} else {
				truba->head = elem->next;
			}
			if(elem->next) {
					elem->next->prev = elem->prev;
			} else {
				truba->last = elem->next;
			}
			next = elem->next;
			free(elem);
			elem = next;
		} else if(elem) elem = elem->next;
	}
	return 1;
}

//Взять первый элемент из очереди
int takehead_truba(truba_t *truba, int *a){
	ochered_t *elem;
	if(!truba || !truba->head){
		fprintf(stderr,"Segmentation fault, Stack is empty!\n");
		return 0;
	}
	*a = truba->head->value;
	elem = truba->head->next;
	free(truba->head);
	truba->head = elem;
	if(truba->head){
		truba->head->prev = NULL;
	} else {
		truba->last = NULL;
		truba->head = NULL;
	}
	return 1;
}

//Взять последний элемент из очереди
int takelast_truba(truba_t *truba, int *a){
	ochered_t *elem;
	if(!truba || !truba->last){
		fprintf(stderr,"Segmentation fault, Stack is empty!\n");
		return 0;
	}
	*a = truba->last->value;
	elem = truba->last->prev;
	free(truba->last);
	truba->last = elem;
	if(truba->last){
		truba->last->next = NULL;
	} else {
		truba->last = NULL;
		truba->head = NULL;
	}
	return 1;
}
void show_truba(truba_t *truba){
	ochered_t *elem = truba->head;
	if(!elem) fprintf(stderr,"Segmentation fault, Stack is empty!\n");
	while(elem){
			printf("%d ",elem->value);
			elem = elem->next;
	}
}
