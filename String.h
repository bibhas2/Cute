/**
 * This is a very simple String class. The design goal is to use a very light
 * weight String utility that can be used in a C program without any
 * external dependency.
 */
typedef struct _String {
	char *buffer;
	int length;
	int capacity;
} String;

/**
 * Create a new String with capacity.
 */
String* newString(int capacity);
/**
 * Adds a char to the end of the String. Grows the String if needed.
 * A String is grown by double the current capacity.
 */
void stringAppendChar(String *str, char ch);
/**
 * Append a character buffer to the end of the String.
 */
void stringAppendBuffer(String *str, const char *buffer, int length);
/**
 * Append a String to the end of the String.
 */
void stringAppendString(String *str, String *toAdd);
/**
 * returns the internal buffer of a String as a NULL terminated C string.
 * The returned buffer belongs to the String object and should not be freed
 * by the caller.
 */
const char* stringAsCString(String *str);
/**
 * Trims a String of white space from head as well as tail.
 */
void stringTrim(String *str);
/**
 * Safely gets character at an index after bounds checking.
 */
char stringGetChar(String *str, int index);
/**
 * Safely sets character at an index after bounds checking.
 */
void stringSetChar(String *str, int index, char ch);
/**
 * Frees memory for a String.
 */
void deleteString(String *str);
