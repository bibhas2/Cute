/**
 * This is a very simple String class. The design goal is to use a very light
 * weight String utility that can be used in a C program without any
 * external dependency.
 */
typedef struct _String {
	char *buffer;
	size_t length;
	size_t capacity;
} String;

/**
 * Creates a new empty String with capacity for 65 characters.
 */
String* newString();
/**
 * Create a new empty String with capacity.
 */
String* newStringWithCapacity(size_t capacity);
/**
 * Creates a new String initialized with a C String.
 */
String* newStringWithCString(const char *str);
/**
 * Creates a new String initialized with a String.
 */
String* newStringWithString(String *str);
/**
 * Adds a char to the end of the String. Grows the String if needed.
 * A String is grown by double the current capacity.
 */
void stringAppendChar(String *str, char ch);
/**
 * Append a character buffer to the end of the String.
 */
void stringAppendBuffer(String *str, const char *buffer, size_t length);
/**
 * Append a String to the end of the String.
 */
void stringAppendString(String *str, String *toAdd);
/**
 * Append a C string to the end of the String.
 */
void stringAppendCString(String *str, const char* toAdd);
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
char stringGetChar(String *str, size_t index);
/**
 * Safely sets character at an index after bounds checking.
 */
void stringSetChar(String *str, size_t index, char ch);
/**
 * Compare two strings. Returns 1 if two strings match, 0 otherwise.
 * This function will perform better than strncmp in some cases because
 * a few extra trivial testing based on length and pointer equality is done.
 */
int stringEquals(String *str1, String *str2);
int stringEqualsCString(String *str1, const char *str2);
int stringStartsWith(String *str1, String *str2);
int stringStartsWithCString(String *str1, const char *str2);

/**
 * Reads a line from a file into a string. Carriage returns (\r and \n)
 * are not included in the string.
 */
void stringReadLine(String *str, FILE *file);

/**
 * Frees memory for a String.
 */
void deleteString(String *str);
