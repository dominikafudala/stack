#pragma once
#pragma warning (disable : 4996)

#ifndef DATA_H
#define DATA H

enum MAJOR
{
	COMPUTER_SCIENCE,
	MATHEMATICS,
	ARCHITECTURE,
	MAJOR_TOTAL
};


struct MY_STUDENT
{
	int year;
	enum MAJOR degree;
	size_t length;
	char *lastname;
};

void data_free(void *ptr);
void *data_init(char *lname, int year, enum MAJOR maj);
void *data_push(char *lastname, int year, enum MAJOR maj);
void data_print(void *ptr);
int data_lastname(void *currdata, void *searchdata);
int data_year(void *currdata, void *searchdata);
int data_major(void *currdata, void *searchdata);
int data_save(void *ptr, FILE *filename);
void *data_load(FILE *filename);
#endif // !DATA_H


