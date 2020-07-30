#pragma once

#ifndef ERRORS_H
#define ERRORS_H

enum ERROR_MESSAGES {
	ALLOC_ERR, //0
	STACK_UNDERFLOW, //1
	FATAL_ERR, //2
	TOTAL_ERR
};

void myError(enum ERROR_MESSAGES num);
void file_err(FILE *fileptr, __int64 *fdesc);

#endif
