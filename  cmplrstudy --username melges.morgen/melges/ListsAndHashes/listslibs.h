/*
 * listslib.h
 *
 *  Created on: 25.11.2009
 *      Author: Morgen Matvey MIPT
 *      		Group 914 Room 432a
 */
#ifndef LISTSLIBS_H_
#define LISTSLIBS_H_
#include <malloc.h>
#include <stdio.h>
#endif /* LISTSLIBS_H_ */

//Создаём тип - структуру для стека
typedef struct list {
	int value;
	struct list *next;
	struct list *prev;
	int delete;
} list_t;

//Тип - структура с указателем на начало стека
typedef struct stack {
	list_t *head;
} stack_t;

//Конструктор стека
stack_t* create_stack(void);

//Деструктор стека
void destroy_stack(stack_t *stack);

//Функция добавления элемента в стек add_stack
void add_stack(stack_t *stack, int a);

//Функция удаляющая элементы содержащие а
int remove_stack(stack_t *stack, int a);

//Функция возвращающая значение элемента стека take_stack
int take_stack(stack_t *stack, int *a);

//Функция отображающая все элементы списка
void show_stack(stack_t *stack);
