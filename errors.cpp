#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "my_stack.h"

static char *errormess[] =
{
	(char *)"E!!!Memory allocation error!!!",
	(char *)"W!!!Stack underflow!!!",
	(char *)"E!!!Fatal error!!!"
};

void myError(enum ERROR_MESSAGES num)
{
	puts(errormess[num] + 1);

	if (errormess[num][0] == 'E')
	{
		free_stack();
		system("pause");
	}
		
	return;
}

void file_err(FILE *fileptr, __int64 *fdesc)
{
	if (fileptr)
		fclose(fileptr);
	if (fdesc)
		free(fdesc);

	myError(FATAL_ERR);
	system("pause");
	exit(1);
}