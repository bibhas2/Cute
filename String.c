#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "String.h"

String*
newString() {
	return newStringWithCapacity(65);
}

String*
newStringWithCapacity(size_t capacity) {
	String* str = malloc(sizeof(String));

	assert(str != NULL);

	str->buffer = malloc(sizeof(char) * capacity);
	assert(str->buffer != NULL);

	str->capacity = capacity;
	str->length = 0;

	return str;
}

String*
_newStringWithBuffer(const char *buffer, size_t length) {
	String* str = malloc(sizeof(String));

	assert(str != NULL);

	str->capacity = length + 65; //A bit of extra room
	str->length = length;
	str->buffer = malloc(sizeof(char) * str->capacity);
	assert(str->buffer != NULL);

	memcpy(str->buffer, buffer, length);

	return str;
}

String* 
newStringWithCString(const char *str) {
	return _newStringWithBuffer(str, strlen(str));
}

String* 
newStringWithString(String *str) {
	return _newStringWithBuffer(str->buffer, str->length);
}

void
stringAppendChar(String *str, char ch) {
	if (str->length == str->capacity) {
		str->buffer = realloc(str->buffer,
			str->capacity * sizeof(char) * 2);
		assert(str->buffer != NULL);
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
stringAppendBuffer(String *str, const char *buffer, size_t length) {
	//Do we have room to fit the string?
	if (length <= (str->capacity - str->length)) {
		memcpy(str->buffer + str->length,
			buffer,
			length);
		str->length = str->length + length;

		return;
	}
	//Grow the string to twice the new length
	size_t newLength = str->length + length;
	str->capacity = 2 * newLength;
	str->buffer = realloc(str->buffer, str->capacity * sizeof(char));
	assert(str->buffer != NULL);
	memcpy(str->buffer + str->length,
		buffer,
		length);
	str->length = newLength;
}

const char*
stringAsCString(String *str) {
	stringAppendChar(str, '\0');
	/*
	 * Don't count the trailing '\0' in length. This will cause
	 * any append operation to correctly overwrite the '\0'.
	 */
	str->length = str->length - 1;

	return str->buffer;
}

void
stringTrim(String *str) {
	if (str->length == 0) {
		return;
	}

	size_t start, end;

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
stringGetChar(String *str, size_t index) {
	assert(index >= 0 && index < str->length);

	return str->buffer[index];
}

void 
stringSetChar(String *str, size_t index, char ch) {
	assert(index >= 0 && index < str->length);

	str->buffer[index] = ch;
}

int 
stringEquals(String *str1, String *str2) {
	if (str1 == str2) {
		return 1;
	}
	if (str1 == NULL || str2 == NULL) {
		return 0;
	}
	if (str1->length != str2->length) {
		return 0;
	}

	return strncmp(str1->buffer, str2->buffer, str1->length) == 0;
}

void
deleteString(String *a) {
	free(a->buffer);
	a->buffer = NULL;
	free(a);
}
