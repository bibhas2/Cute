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
 * Creates a new empty String with capacity for 65 characters.
 */
String* newString();
/**
 * Create a new empty String with capacity.
 */
String* newStringWithCapacity(int capacity);
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
 * Compare two strings. Returns 1 if two strings match, 0 otherwise.
 * This function will perform better than strncmp in some cases because
 * a few extra trivial testing based on length and pointer equality is done.
 */
int stringEquals(String *str1, String *str2);
/**
 * Frees memory for a String.
 */
void deleteString(String *str);
