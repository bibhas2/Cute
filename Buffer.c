#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Buffer.h"

Buffer* newBuffer() {
	return newBufferWithCapacity(256);
}

Buffer*
newBufferWithCapacity(int capacity) {
	Buffer* buffer = malloc(sizeof(Buffer));

	buffer->buffer = malloc(sizeof(char) * capacity);
	buffer->capacity = capacity;
	buffer->length = 0;
	buffer->position = 0;

	return buffer;
}

Buffer* newBufferWithBytes(const char *bytes, int length) {
	Buffer* buffer = malloc(sizeof(Buffer));

	buffer->capacity = length + 65; //A bit of extra room
	buffer->length = length;
	buffer->position = 0;
	buffer->buffer = malloc(sizeof(char) * buffer->capacity);

	memcpy(buffer->buffer, bytes, length);

	return buffer;
}

Buffer* newBufferWithBuffer(Buffer *buffer) {
	return newBufferWithBytes(buffer->buffer, buffer->length);
}

void bufferAppendByte(Buffer *buffer, char ch) {
	if (buffer->length == buffer->capacity) {
		buffer->buffer = realloc(buffer->buffer,
			buffer->capacity * sizeof(char) * 2);
		buffer->capacity *= 2;
	}

	buffer->buffer[buffer->length] = ch;
	buffer->length += 1;
}

void
bufferAppendBytes(Buffer *buffer, const char *bytes, int length) {
	//Do we have room to fit the buffer?
	if (length <= (buffer->capacity - buffer->length)) {
		memcpy(buffer->buffer + buffer->length, bytes, length);
		buffer->length = buffer->length + length;

		return;
	}
	//Grow the buffer to twice the new length
	int newLength = buffer->length + length;
	buffer->capacity = 2 * newLength;
	buffer->buffer = realloc(buffer->buffer, buffer->capacity * sizeof(char));
	memcpy(buffer->buffer + buffer->length, bytes, length);
	buffer->length = newLength;
}

char bufferGetByte(Buffer *buffer, int index) {
	assert(index >= 0 && index < buffer->length);

	return buffer->buffer[index];
}

void bufferSetByte(Buffer *buffer, int index, char byte) {
	assert(index >= 0 && index < buffer->length);

	buffer->buffer[index] = byte;
}

char bufferNextByte(Buffer *buffer) {
	assert(buffer->position < buffer->length);

	char byte = buffer->buffer[buffer->position];

	buffer->position += 1;

	return byte;
}

void deleteBuffer(Buffer *a) {
	free(a->buffer);
	a->buffer = NULL;
	free(a);
}
