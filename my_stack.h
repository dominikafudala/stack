#pragma once

#ifndef MY_STACK_H
#define MY_STACK_H
#pragma warning (disable : 4996)


struct STACK {
	void *val; //pointer to data
	struct STACK *nextNode; //pointer to next element
};

typedef void(*NoData)(void *pdata);
typedef void(*PrintObject)(void * pdata);
typedef int(*File)(void *pdata, FILE *file);
typedef void*(*Load)(FILE *file);
typedef int(Find)(void *currdata, void *searchdata);

void init_stack(NoData ptr, PrintObject display, File save, Load load);
void display_stack();
STACK * push_to_stack(void *ptrData);
void *pop_stack();
void free_stack();
void *search_stack(void *searchdata, Find search_ptr, int iffirst);
void save_stack();
void load_stack();

#endif