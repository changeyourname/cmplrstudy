/*
 * worklists.c
 * Encoding is UTF-8, author from Russia and using russian dictionary
 *  Created on: 30.11.2009
 *      Author: Morgen Matvey MIPT
 *				Group 914 Room 432a
 */
#include <stdio.h>
#include <stdlib.h>
#include "listslibs.h"
#include "ocheredilibs.h"
//boost.h stl.h
void work_stake(void);

void work_truba(void);

int main()
{
	printf("С чем будете работать?\n 1 - C односвязным стеком\n 2 - С двусвязным списком\n");
	char wichuse;
	scanf("%c", &wichuse);
	switch(wichuse){
	case '1':
		work_stake();
		break;
	case '2':
		work_truba();
	}
		return 0;
}

void work_stake(void){
	stack_t *stack = create_stack();
		//Выводим пользователю доступные действия
		char action;
		while(action != '7'){
			printf("Выберите действие\n 1 - Добавить элемент в стек\n "
				"2 - Удалить элемент из стека\n 3 - Взять последний элемент из стека\n"
				" 4 - Очистить стек\n 5 - Показать весь список\n 6 - Создать список задачи 1.2\n 7 - Выйти\n");
			scanf(" %c",&action);
			//Делаем выборку
			switch(action){
			case '1':
				printf("Введите значение элемента\n");
				int add_value;
				scanf(" %d",&add_value);
				add_stack(stack, add_value);
				break;
			case '2':
				printf("Введите значение элемента для удаления\n");
				int delete_value;
				scanf("%d",&delete_value);
				remove_stack(stack, delete_value);
				break;
			case '3':
				printf("OK\n");
				int a;
				if(take_stack(stack,&a)) printf("%d\n",a);
				break;
			case '4':
				destroy_stack(stack);
				stack = create_stack();
				break;
			case '5':
				show_stack(stack);
				putchar('\n');
				break;
			case '6':
				printf("Это уничтожит существующий стек! Введите 0 для отмены\nВведите N\n");
				int n;
				scanf("%d",&n);
				if(n<1) break;
				destroy_stack(stack);
				stack = create_stack();
				for(int i=1;i<=n;i++){
					add_stack(stack,i);
				}
				break;
			default:
				fprintf(stderr,"Illegal input\n");
				break;
			}
		}
}

void work_truba(void){
	truba_t *stack = create_truba();
	char action;
	while(action != '8'){
		printf("Выберите действие\n 1 - Добавить элемент в начало очереди\n"
				" 2 - Добавить элемент в конец очереди\n 3 - Взять первый элемент из очереди\n"
				" 4 - Взять последний элемент из очереди\n 5 - Показать всю очередь\n 6 - Удалить элемент из очереди\n"
				" 7 - Очистить очередь\n 8 - Выйти\n");
		scanf(" %c", &action);
		switch(action){
		case '1':
			printf("Введите значение элемента\n");
			int add_valuehead;
			scanf("%d",&add_valuehead);
			addhead_truba(stack,add_valuehead);
			break;
		case '2':
			printf("Введите значение элемента\n");
			int add_valuelast;
			scanf(" %d",&add_valuelast);
			addlast_truba(stack,add_valuelast);
			break;
		case '3':
			printf("\nOK\n");
			int a;
			if(takehead_truba(stack, &a))
			printf("%d\n",a);
			break;
		case '4':
			printf("\nOK\n");
			if(takelast_truba(stack, &a))
			printf("%d\n",a);
			break;
		case '5':
			show_truba(stack);
			putchar('\n');
			break;
		case '6':
			printf("Введите значение элемента для удаления\n");
			int delete_value;
			scanf("%d",&delete_value);
			remove_truba(stack, delete_value);
			break;
		case '7':
			destroy_truba(stack);
			stack = create_truba();
			break;
		default:
			fprintf(stderr, "Illegal input\n");
			break;
		}
	}
}
