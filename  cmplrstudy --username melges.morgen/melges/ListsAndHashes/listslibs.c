/*
 * listslibs.c
 * Encoding is UTF-8, author from Russia and use russian dictionary
 *  Created on: 14.12.2009
 *      Author: Morgen Matvey MIPT
 *				Group 914 Room 432a
 */
#include "listslibs.h"

//Конструктор стека
stack_t* create_stack(void){
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	stack->head = NULL;
	return stack;
}

//Деструктор стека
void destroy_stack(stack_t *stack){
	list_t *next, *elem = stack->head;
	while(elem) {
		next = elem->next;
		free(elem);
		elem = next;
	}
	free(stack);
}
//Функция добавления элемента в стек add_stack
void add_stack(stack_t *stack, int a){
	list_t *elem = (list_t*)malloc(sizeof(list_t));
	elem->value = a;
	elem->delete = 0;
	elem->next = stack->head;
	stack->head = elem;
}
//Функция удаляющая элементы содержащие а
int remove_stack(stack_t *stack, int a){
	list_t *elem = stack->head;
	list_t *nextnext;
	if(!elem){
		fprintf(stderr,"Segmentation fault, Stack is empty!\n");
		return 0;
	}
	while(elem->next){
		if(elem->next->value == a){
			nextnext = elem->next->next;
			free(elem->next);
			elem->next = nextnext;
		} else if(elem->next) elem = elem->next;
	}
	if(stack->head->value == a){
		stack->head = stack->head->next;
	}
	return 1;
}
//Функция возвращающая значение элемента стека take_stack
int take_stack(stack_t *stack, int *a){
	list_t *elem;
	if(!stack || !stack->head){
		fprintf(stderr,"Segmentation fault, Stack is empty!\n");
		return 0;
	}
	*a = stack->head->value;
	elem = stack->head->next;
	free(stack->head);
	stack->head = elem;
	return 1;
}
//Функция отображающая все элементы списка
void show_stack(stack_t *stack){
	list_t *elem = stack->head;
	while(elem){
		printf("%d ",elem->value);
		elem = elem->next;
	}
}
