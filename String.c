#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "String.h"

String*
newString(int capacity) {
	String* a = malloc(sizeof(String));

	a->buffer = malloc(sizeof(char) * capacity);
	a->capacity = capacity;
	a->length = 0;

	return a;
}

void
_stripTrailChar(String *str) {
	if (str->length > 0 && str->buffer[str->length - 1] == '\0') {
		str->length = str->length - 1;
	}
}

void
stringAppendChar(String *str, char ch) {
	_stripTrailChar(str);

	if (str->length == str->capacity) {
		str->buffer = realloc(str->buffer,
			str->capacity * sizeof(char) * 2);
		str->capacity *= 2;
	}

	str->buffer[str->length] = ch;
	str->length += 1;
}

void 
stringAppendString(String *str, String *toAdd) {
	stringAppendBuffer(str, toAdd->buffer, toAdd->length);
}

void
stringAppendBuffer(String *str, const char *buffer, int length) {
	_stripTrailChar(str);

	//Do we have room to fit the string?
	if (length <= (str->capacity - str->length)) {
		memcpy(str->buffer + str->length,
			buffer,
			length);
		str->length = str->length + length;

		return;
	}
	//Grow the string
	int newLength = str->length + length;
	int multiplier = (int) ceil(
		(double) newLength / (double) str->capacity);
	str->capacity *= multiplier;
	str->buffer = realloc(str->buffer, str->capacity * sizeof(char));
	memcpy(str->buffer + str->length,
		buffer,
		length);
	str->length = newLength;
}

char*
stringAsCString(String *str) {
	if (str->length == 0 || str->buffer[str->length - 1] != '\0') {
		stringAppendChar(str, '\0');
	}

	return str->buffer;
}

void
stringTrim(String *str) {
	if (str->length == 0) {
		return;
	}

	int start, end;

	for (start = 0; start < str->length; ++start) {
		if (!isspace(str->buffer[start])) {
			break;
		}
	}

	for (end = str->length - 1; end >= 0; --end) {
		if (!isspace(str->buffer[end])) {
			break;
		}
	}
	//All spaces?
	if (end < 0) {
		str->length = 0;

		return;
	}
	//Trim start
	if (start > 0) {
		memmove(str->buffer, str->buffer + start, str->length - start);
	}
	//Trim end
	str->length = end  - start + 1;
}

char 
stringGetChar(String *str, int index) {
	assert(index >= 0 && index < str->length);

	return str->buffer[index];
}

void 
stringSetChar(String *str, int index, char ch) {
	assert(index >= 0 && index < str->length);

	str->buffer[index] = ch;
}

void
deleteString(String *a) {
	free(a->buffer);
	a->buffer = NULL;
	free(a);
}
