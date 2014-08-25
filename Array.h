/**
 * A very simple implementation of dynamic arry in C. It
 * can be used readily in the simplest of C program without any
 * external dependency.
 */
typedef struct _Array {
	void **buffer;
	size_t length;
	size_t capacity;
} Array;

/**
 * Create a new Array with capacity.
 */
Array* newArray(size_t capacity);
/**
 * Get the object at an index after doing bounds checking.
 */
void* arrayGet(Array *a, size_t index);
/**
 * Set the object at an index after doing bounds checking.
 */
void* arraySet(Array *a, size_t index, void *obj);
/**
 * Add a new object at the end of the array. The array is grown if needed.
 * Every time an array is grown, it's capacity is doubled. This is done
 * to minimize growth in a fast growing array.
 */
void arrayAdd(Array *a, void *obj);
/**
 * Frees up memory for an Array.
 */
void deleteArray(Array *a);
