#include <stdlib.h>
#include <stdio.h>
#include "random.h"

#pragma warning (disable : 4996)

int int_input()
{
	int number, flag = 1;

	while (flag) {
		if (scanf("%d", &number) == 1 && number >= 0)
			flag = 0;
		else
		{
			printf("Input number that is equal or greater than 0\n");
		}

		while (getchar() != '\n');
	}

	return number;
}

int int_input_max(int max)
{
	int number, flag = 1;

	while (flag) {
		if (scanf("%d", &number) == 1 && number >= 0 && number < max)
			flag = 0;
		else
		{
			printf("Input number that is equal or greater than 0 and equal or less than %d\n", max-1);
		}

		while (getchar() != '\n');
	}

	return number;
}