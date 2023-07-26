#define DYNSTR_IMPLEMENTATION
#include "../dynstr.h"
#include <stdio.h>

int main()
{
	strarr arr;
	init_strarr(&arr);
	strarr_push(&arr, "test1");
	strarr_push(&arr, "string1");
	strarr_push(&arr, "hellostring");
	strarr_push(&arr, "kappa");
	strarr_clear(&arr, 2);
	printf("%s\n", strarr_get(&arr, 0));
	printf("%s\n", strarr_get(&arr, 1));
	printf("%s\n", strarr_get(&arr, 2));
	printf("%s\n", strarr_get(&arr, 3));
	return 0;
}
