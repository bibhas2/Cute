#include <stdio.h>
#include "String.h"

int
main() {
	String *str1 = newStringWithCString("Hello World");
	String *str2 = newStringWithCapacity(2);

	stringAppendBuffer(str2, "ab", 2);

	printf("%s:%s\n", stringAsCString(str1), stringAsCString(str2));
	printf("%s:%s\n", stringAsCString(str1), stringAsCString(str2));

	stringAppendBuffer(str2, "cd", 2);

	printf("%s:%s\n", stringAsCString(str1), stringAsCString(str2));
	printf("%s:%s\n", stringAsCString(str1), stringAsCString(str2));
	printf("%s:%s\n", stringAsCString(str1), stringAsCString(str2));
	printf("%d:%d\n", str1->length, str2->length);
	printf("Equals: %d\n", stringEquals(str1, str2));
	printf("Equals: %d\n", stringEquals(str1, str1));
}
