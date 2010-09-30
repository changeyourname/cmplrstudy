/*
 * ocheredilibs.h
 * Encoding is UTF-8, author from Russia and use russian dictionary
 *  Created on: 06.12.2009
 *      Author: Morgen Matvey MIPT
 *				Group 914 Room 432a
 */
#ifndef OCHEREDILIBS_H_
#define OCHEREDILIBS_H_
#include <malloc.h>
#include <stdio.h>
#endif /* OCHEREDILIBS_H_ */

typedef struct ochered {
	int value;
	struct ochered *next;
	struct ochered *prev;
	int gonext;
} ochered_t;
typedef struct truba {
	ochered_t *head;
	ochered_t *last;
} truba_t;

//Создаём очередь
truba_t* create_truba();

//Деструктор очереди
void destroy_truba(truba_t *truba);

//Вставка элемента в начало
void addhead_truba(truba_t *truba, int a);

//Вставка элемента в конец
void addlast_truba(truba_t *truba, int a);

//Удаление элементов содержащих а
int remove_truba(truba_t *truba, int a);

//Взять первый элемент из очереди
int takehead_truba(truba_t *truba, int *a);

//Взять последний элемент из очереди
int takelast_truba(truba_t *truba, int *a);

void show_truba(truba_t *truba);
