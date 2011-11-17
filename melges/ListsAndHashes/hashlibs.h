/*
 * hashlibs.h
 *
 *  Created on: 30.11.2009
 *      Author: Morgen Matvey MIPT
 *				Group 914 Room 432a
 */

#ifndef HASHLIBS_H_
#define HASHLIBS_H_

#endif /* HASHLIBS_H_ */

//Функции преобразующие строку в хеш
unsigned int hash_f1(char* key){
	for(int result=0;*key != 0;key++)
		result = result*31+*key;
	return result;
}

unsigned int hash_f2(char* key){
	for(int result=0;*key != 0;key++)
		result = result*7+*key;
	return result;
}
