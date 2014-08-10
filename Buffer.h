/**
 * This is a very simple Buffer class. The design goal is to use a very light
 * weight bounds checked Buffer utility that can be used in a C program without any
 * external dependency.
 */
typedef struct _Buffer {
	char *buffer;
	int position;
	int length;
	int capacity;
} Buffer;

/**
 * Creates a new empty Buffer with capacity for 256 bytes.
 */
Buffer* newBuffer();
/**
 * Create a new empty Buffer with capacity.
 */
Buffer* newBufferWithCapacity(int capacity);
/**
 * Creates a new Buffer object by copying the supplied bytes.
 */
Buffer* newBufferWithBytes(const char *bytes, int length);
/**
 * Creates a new Buffer by copying another Buffer.
 */
Buffer* newBufferWithBuffer(Buffer *buffer);
/**
 * Adds a byte to the end of the Buffer. Grows the Buffer if needed.
 * A Buffer is grown by double the current capacity.
 */
void bufferAppendByte(Buffer *buffer, char ch);
/**
 * Append a character buffer to the end of the Buffer. Buffer is grown if needed.
 */
void bufferAppendBytes(Buffer *buffer, const char *bytes, int length);
/**
 * Append a Buffer to the end of the Buffer. Buffer is grown if needed.
 */
void bufferAppendBuffer(Buffer *buffer, Buffer *toAdd);
/**
 * Gets the next byte in sequence. Sequence always starts at 0. 
 * This method increments the sequential position.
 */
char bufferNextByte(Buffer *buffer);
/**
 * Safely gets a byte at an index after bounds checking.
 */
char bufferGetByte(Buffer *buffer, int index);
/**
 * Safely sets byte at an index after bounds checking.
 */
void bufferSetByte(Buffer *buffer, int index, char ch);
/**
 * Frees memory for a Buffer.
 */
void deleteBuffer(Buffer *buffer);
