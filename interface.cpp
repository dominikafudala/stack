#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "my_stack.h"
#include "errors.h"
#include "random.h"

#pragma warning (disable : 4996)

static char *tab[] =
{
	(char *)"0 - push",
	(char *)"1 - pop",
	(char *)"2 - clear stack",
	(char *)"3 - find",
	(char *)"4 - save to file",
	(char *)"5 - load from file",
	(char *)"6 - exit"
};

static char *majors[] =
{
	(char *)"0 - computer science",
	(char *)"1 - mathematics",
	(char *)"2 - architecture"
};

static char *search[] =
{
	(char *)"0 - Lastname",
	(char *)"1 - Year",
	(char *)"2 - Major"
};

void myMenu()
{
	init_stack(data_free, data_print, data_save, data_load);
	int opt = 0;
	while (1)
	{

		display();
		show_menu();
		opt = int_input_max(INTERFACE_TOTAL);
		switch (opt)
			{
		case INTERFACE_PUSH: push();
			break;
		case INTERFACE_POP: pop();
			break;
		case INTERFACE_CLEAR: clear();
			break;
		case INTERFACE_FIND: find();
			break;
		case INTERFACE_SAVE: save();
			break;
		case INTERFACE_LOAD: load();
			break;
		case INTERFACE_EXIT: clear();
			return;
		default:
			printf("There is no such option! Try again. \n\n");
			};
	}
}

void show_menu()
{
	size_t k;
	for (k = 0; k < INTERFACE_TOTAL; ++k)
	{
		printf("%s\n", tab[k]);
	}
}

void show_majors() {
	size_t k;
	for (k = 0; k < MAJOR_TOTAL; ++k)
	{
		printf("%s\n", majors[k]);
	}
}

void display() {
	display_stack();
}

void push()
{
	int flag = 1;
	char lastname[256];
	int year, major;
	printf("Input lastname:\n");
	scanf_s("%s", lastname, (unsigned)sizeof(lastname));
	printf("Input year:\n");
	year = int_input();
	printf("Choose major:\n");
	show_majors();
	major = int_input_max(MAJOR_TOTAL);
	printf("\n");

	void *ptrData = data_push(lastname, year, (MAJOR)major);
	if (!push_to_stack(ptrData))
		myError(ALLOC_ERR);

}

void pop()
{
	void *tmp = pop_stack();
	if (tmp != NULL) {
		printf("\n\nData popped:\n");
		data_print(tmp);
		printf("\n\n");
	}
	data_free(tmp);
}

void clear()
{
	free_stack();
}

void find()
{
	size_t k, choose;
	printf("\nChoose what you want to find:\n");
	for (k = 0; k < SEARCH_TOTAL; ++k)
	{
		printf("%s\n", search[k]);
	}
	choose = int_input_max(MAJOR_TOTAL);
	switch (choose)
	{
	case LASTNAME_SEARCH: find_lastname();
		break;
	case YEAR_SEARCH: find_year();
		break;
	case MAJOR_SEARCH: find_major();
		break;
	default:
		printf("There is no such option! Try again. \n");
	};
}

void find_lastname()
{
	char lnsearch[256];
	printf("Input lastname:\n");
	scanf_s("%s", lnsearch, (unsigned)sizeof(lnsearch));

	MY_STUDENT *searchdata = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));

	if (!searchdata)
	{
		myError(ALLOC_ERR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));
	size_t size = strlen(lnsearch) + 1;
	searchdata->lastname = (char *)malloc(size * sizeof(char));

	if (!searchdata->lastname)
	{
		myError(ALLOC_ERR);
		return;
	}
	strcpy(searchdata->lastname, lnsearch);

	void *ptrsearch = search_stack(searchdata, data_lastname, 1);

	if (ptrsearch)
	{
		printf("Data found: \n");
		data_print(ptrsearch);
	}
	else
		printf("No data found!");

	while (ptrsearch)
	{
		ptrsearch = search_stack(searchdata, data_lastname, 0);
		if (ptrsearch)
		{
			data_print(ptrsearch);
		}
	}
	printf("\n\n");

	data_free(searchdata);
}

void find_year()
{
	int yearsearch;
	printf("Input year:\n");
	yearsearch = int_input();

	MY_STUDENT *searchdata = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));

	if (!searchdata)
	{
		myError(ALLOC_ERR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));

	searchdata->year = yearsearch;

	void *ptrsearch = search_stack(searchdata, data_year, 1);

	if (ptrsearch)
	{
		printf("Data found: \n");
		data_print(ptrsearch);
	}
	else
		printf("No data found!");

	while (ptrsearch)
	{
		ptrsearch = search_stack(searchdata, data_year, 0);
		if (ptrsearch)
		{
			data_print(ptrsearch);
		}
	}
	printf("\n\n");

	data_free(searchdata);
}

void find_major()
{
	int majorsearch;
	printf("Choose major:\n");
	show_majors();
	majorsearch = int_input_max(MAJOR_TOTAL);

	MY_STUDENT *searchdata = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));

	if (!searchdata)
	{
		myError(ALLOC_ERR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));

	searchdata->degree = (MAJOR)majorsearch;

	void *ptrsearch = search_stack(searchdata, data_major, 1);

	if (ptrsearch)
	{
		printf("Data found: \n");
		data_print(ptrsearch);
	}
	else
		printf("No data found!");

	while (ptrsearch)
	{
		ptrsearch = search_stack(searchdata, data_major, 0);
		if (ptrsearch)
		{
			data_print(ptrsearch);
		}
	}
	printf("\n\n");

	data_free(searchdata);

}

void save() {
	save_stack();
}


void load() {
	load_stack();
}