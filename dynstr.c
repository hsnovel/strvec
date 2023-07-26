#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	unsigned char *data;
	size_t* offset;

	size_t offset_cap;
	size_t offset_size;
	size_t index;

	size_t data_cap;
	size_t data_size;
} strarr;

#ifndef STRARR_INITIAL_DATA_CAP
#define STRARR_INITIAL_DATA_CAP 10
#endif

#ifndef STRARR_INITIAL_STR_COUNT
#define STRARR_INITIAL_STR_COUNT 2
#endif

int init_strarr(strarr *arr)
{
	arr->data = malloc(STRARR_INITIAL_DATA_CAP * sizeof(unsigned char));
	if (arr->data == NULL)
		return 0;

	arr->offset = malloc(STRARR_INITIAL_STR_COUNT * sizeof(size_t));
	if (arr->offset == NULL) {
		free(arr->data);
		return 0;
	}

	arr->data_cap = STRARR_INITIAL_DATA_CAP;
	arr->offset_cap = STRARR_INITIAL_STR_COUNT;
	arr->offset_size = 0;
	arr->data_size = 0;
	arr->index = 0;

	return 1;
}

int strarr_push(strarr *arr, unsigned char* str)
{
	if (arr->offset_size >= arr->offset_cap) {
		size_t newcap = arr->offset_cap * 10;
		size_t *tmp = malloc(newcap);
		memcpy(tmp, arr->offset, arr->offset_size);
		arr->offset_cap = newcap;
		if (tmp == NULL)
			return 0;
		free(arr->offset);
		arr->offset = tmp;
	}

	int len = strlen(str);
	len++; // \0 character
	if (arr->data_size >= arr->data_cap) {
		size_t newcap = (arr->data_cap * 10) + len;
		unsigned char *tmp = malloc(newcap);
		memcpy(tmp, arr->data, arr->data_size);
		arr->data_cap = newcap;
		if (tmp == NULL)
			return 0;
		arr->data = tmp;
	}

	unsigned char *ptr = arr->data + arr->offset_size;
	memcpy(ptr, str, len);
	arr->offset[arr->index] = ptr - arr->data;
	arr->index++;
	arr->offset_size += len;

	return 1;
}

int strarr_clear(strarr *arr, int index)
{
	int i = 0;
	unsigned char *start = arr->data + arr->offset[index];
	while (start[i] != '\0') {
		i++;
	}
	memset(start, 0, i);
}

extern inline unsigned char *strarr_get(strarr *arr, int index)
{
	assert(index < arr->index);
	return arr->data + arr->offset[index];
}

int main()
{
	strarr arr;
	init_strarr(&arr);
	strarr_push(&arr, "test");
	strarr_push(&arr, "lolsdasdsads");
	strarr_push(&arr, "2142121421");
	strarr_push(&arr, "tedsadwdas");
	strarr_clear(&arr, 2);
	printf("%s\n", strarr_get(&arr, 0));
	printf("%s\n", strarr_get(&arr, 1));
	printf("%s\n", strarr_get(&arr, 2));
	printf("%s\n", strarr_get(&arr, 3));
	return 0;
}
