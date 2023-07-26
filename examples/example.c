#define DYNSTR_IMPLEMENTATION
#include "../dynstr.h"
#include <stdio.h>


int main()
{
	strarr arr;
	strarr_init(&arr);
	strarr_push(&arr, "test1");
	strarr_push(&arr, "string1");
	strarr_push(&arr, "hellostring");
	strarr_push(&arr, "kappa");
	strarr_clear(&arr, 2);
	printf("%s\n", strarr_get(&arr, 0));
	printf("%s\n", strarr_get(&arr, 1));
	printf("%s\n", strarr_get(&arr, 2));
	printf("%s\n", strarr_get(&arr, 3));

	/* This is how you should NOT use the next function,
	*  the os will clear the memory after you exit the
	*  program so calling free() is unnecesarry unless
	*  the program is running for a long time and you
	*  generate a string in the middle of the program
	*  and need to delete, do not use this before exiting
	*  the program it is unnecesarry. */
	strarr_delete_struct(&arr);
	return 0;
}
