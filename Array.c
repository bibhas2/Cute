#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Array.h"

Array*
newArray(int capacity) {
	Array* a = malloc(sizeof(Array));

	assert(a != NULL);

	a->buffer = malloc(sizeof(void*) * capacity);
	assert(a->buffer != NULL);
	a->capacity = capacity;
	a->length = 0;

	return a;
}

void*
arrayGet(Array *a, int index) {
	assert(index >= 0 && index < a->length);

	return a->buffer[index];
}
void*
arraySet(Array *a, int index, void *obj) {
	assert(index >= 0 && index < a->length);

	a->buffer[index] = obj;

	return obj;
}

void
arrayAdd(Array *a, void *obj) {
	if (a->length == a->capacity) {
		a->buffer = realloc(a->buffer,
			a->capacity * sizeof(void*) * 2);
		assert(a->buffer != NULL);
		a->capacity *= 2;
	}

	a->buffer[a->length] = obj;
	a->length += 1;
}

void
deleteArray(Array *a) {
	free(a->buffer);
	a->buffer = NULL;
	free(a);
}

