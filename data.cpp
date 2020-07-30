#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "string.h"
#include "errors.h"


void data_free(void *ptr) 
{
	MY_STUDENT *ptrData = (MY_STUDENT*)ptr;
	if (ptrData)
	{

		free(ptrData->lastname);
		ptrData->lastname = NULL;
		free(ptrData);
		ptrData = NULL;
	}
}

void * data_init(char *lname, int year, enum MAJOR maj) {
	MY_STUDENT *ptrData = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));
	if (!ptrData) {
		myError(ALLOC_ERR);
		return NULL;
	}
	if (ptrData)
	{	
		size_t size = strlen(lname)+1;
		ptrData->length = size;
		ptrData->lastname = (char *)malloc(size * sizeof(char));
		if (!ptrData->lastname) {
			myError(ALLOC_ERR);
			return NULL;
		}
		strcpy(ptrData->lastname, lname);
		ptrData->year = year;
		ptrData->degree = maj;
	}
	return (void *)(ptrData);
}

void * data_push(char *lastname, int year, enum MAJOR maj) {
	return data_init(lastname, year, maj);
}

void data_print(void *ptr) {
	MY_STUDENT *tmp = (MY_STUDENT*)ptr;
	if (tmp)
	{
		printf("|%-20s|", tmp->lastname);
		printf("%-20d|", tmp->year);
		switch (tmp->degree) {
		case COMPUTER_SCIENCE:
			printf("%-20s|\n", "Computer Science");
			break;
		case MATHEMATICS:
			printf("%-20s|\n", "Mathematics");
			break;
		case ARCHITECTURE:
			printf("%-20s|\n", "Architecture");
			break;
		}
	}
}
int data_lastname(void *currdata, void *searchdata)
{
	MY_STUDENT *ptrcurr = (MY_STUDENT *)currdata;
	MY_STUDENT *ptrsearch = (MY_STUDENT *)searchdata;

	if (strcmp(ptrcurr->lastname, ptrsearch->lastname) == 0)
		return 1;

	return 0;
}

int data_year(void *currdata, void *searchdata)
{
	MY_STUDENT *ptrcurr = (MY_STUDENT *)currdata;
	MY_STUDENT *ptrsearch = (MY_STUDENT *)searchdata;

	if (ptrcurr->year == ptrsearch->year)
		return 1;

	return 0;
}

int data_major(void *currdata, void *searchdata)
{
	MY_STUDENT *ptrcurr = (MY_STUDENT *)currdata;
	MY_STUDENT *ptrsearch = (MY_STUDENT *)searchdata;

	if (ptrcurr->degree == ptrsearch->degree)
		return 1;

	return 0;
}

int data_save(void *ptr, FILE *filename) {
	MY_STUDENT *dataptr = (MY_STUDENT*)ptr;

	if (fwrite(dataptr,sizeof(dataptr->year) + sizeof(dataptr->degree) + sizeof(dataptr->length), 1, filename) != 1)
		return 0;
	if (fwrite(dataptr->lastname, dataptr->length * sizeof(dataptr->lastname[0]), 1, filename) != 1)
		return 0;
	
	return 1;
}

void *data_load(FILE *filename)
{
	MY_STUDENT *tmp = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));
	if (!tmp)
	{
		myError(ALLOC_ERR);
	}

	memset(tmp, 0, sizeof(MY_STUDENT));

	if (fread(tmp, sizeof(tmp->year) + sizeof(tmp->degree) + sizeof(tmp->length), 1, filename) != 1)
		return 0; 
	
	tmp->lastname = (char *)malloc(tmp->length * sizeof(char));
	
	if (fread(tmp->lastname, tmp->length * sizeof(char), 1, filename) != 1)
		return 0;

	void *dataptr = data_push(tmp->lastname, tmp->year, tmp->degree);
	return dataptr;

}