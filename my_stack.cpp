#include <stdlib.h>
#include <stdio.h>
#include "my_stack.h"
#include "errors.h"

static STACK *top = NULL;
char fileName[] = "file.bin";
NoData p_nodata;
PrintObject display;
File savefile;
Load loadfile;

void init_stack(NoData ptr_nodata, PrintObject ddisplay, File ssave, Load lload)
{
	top = NULL;
	p_nodata = ptr_nodata;
	display = ddisplay;
	savefile = ssave;
	loadfile = lload;
}

void display_stack()
{
	STACK *tmp = top;
	if (tmp != NULL) {
		printf("%-29s", " ");
		printf("%s", "STACK");
		printf("\n\n");
		while (tmp != NULL) {
			display(tmp->val);
			tmp = tmp->nextNode;
		}
		printf("\n\n");
	}
	else printf("Stack is empty! Push data or load from the disk!\n\n");

}

STACK * push_to_stack(void *ptrData) {
	STACK *next = (STACK *)malloc(sizeof(STACK));//allocating memory for new elemelnt
	if (!next) {
		myError(ALLOC_ERR);
		return NULL;
	}

	next->val = ptrData;
	next->nextNode = top; // linking old and new element
	top = next; // changing head of the stack to new element

	return next;
}


void *pop_stack()
{
	STACK ret;
	if (!top) {
		myError(STACK_UNDERFLOW);
		return NULL;
	}
	else {
		STACK *next = top->nextNode;
		ret.val = top->val;
		free(top);
		top = next;
		return ret.val;
	}
	
}

void free_stack() {
	STACK *ptr = top, *ptrtmp = NULL;
	while (ptr) {
		(*p_nodata)(ptr->val);
		ptrtmp = ptr;
		ptr = ptr->nextNode;
		free(ptrtmp);
	}
	top = NULL;
}

void *search_stack(void *searchdata, Find search_ptr, int iffirst)
{
	static STACK *ptr;
	STACK *ptrtmp = NULL;
	if (top == NULL)
	{
		myError(STACK_UNDERFLOW);
		return NULL;
	}
	if (iffirst)
		ptr = top;

	while (ptr)
	{
		if (!(*search_ptr)(ptr->val, searchdata))
		{
			ptr = ptr->nextNode;
		}
		else
		{
			ptrtmp = ptr;
			ptr = ptr->nextNode;
			return ptrtmp->val;
		}
	}
	return NULL;
}

void save_stack() {
	STACK *tmp = top;
	if (tmp == NULL) {
		myError(STACK_UNDERFLOW);
		return;
	}

	size_t count = 0;
	while (tmp != NULL) {
		count++;
		tmp = tmp->nextNode;
	}
	tmp = top;

	unsigned int items = (unsigned int)count;
	__int64 *file_desc = (__int64 *)malloc((items + 1) * sizeof(__int64));
	if (!file_desc)
	{
		file_err(NULL, file_desc);
	}

	FILE *pf = fopen(fileName, "wb");
	if (!pf)
	{
		file_err(pf, file_desc);
	}

	if (fwrite(&items, sizeof(unsigned int), 1, pf) != 1)
	{
		file_err(pf, file_desc);
	}

	_fseeki64(pf, (count + 1) * sizeof(__int64), SEEK_CUR);

	size_t item_s = 0;

	while(tmp != NULL) {
		file_desc[item_s] = ftell(pf);
		item_s++;
		if (savefile(tmp->val, pf) != 1)
		{
			file_err(pf, file_desc);
		}
		tmp = tmp->nextNode;
	}

	file_desc[item_s] = ftell(pf);

	_fseeki64(pf, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), count + 1, pf) != count + 1)
		file_err(pf, file_desc);

	if (pf) {
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) {
		free(file_desc);
		file_desc = NULL;
	}
}

void load_stack() {

	free_stack();

	__int64 *file_desc = NULL;
	unsigned int items = 0, item_s, record;
	

	FILE *pf = fopen(fileName, "rb");
	if (!pf)
	{
		file_err(pf, file_desc);
	}

	if (fread(&items, sizeof(unsigned int), 1, pf) != 1)
	{
		file_err(pf, file_desc);
	}

	file_desc = (__int64 *)malloc((items + 1) * sizeof(__int64));
	if (!file_desc)
	{
		file_err(pf, file_desc);
	}

	if (fread(file_desc, sizeof(file_desc[0]), items + 1, pf) != items + 1)
	{
		file_err(pf, file_desc);
	}

	for (item_s = 0; item_s < items; ++item_s)
	{
		record = items - item_s - 1;
		_fseeki64(pf, file_desc[record], SEEK_SET);

		void *ptrdata = loadfile(pf);
		if (!push_to_stack(ptrdata))
		{
			file_err(pf, file_desc);
		}


	}

	if (pf) {
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) {
		free(file_desc);
		file_desc = NULL;
	}
}