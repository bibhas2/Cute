#include <stdio.h>
#include "String.h"

int
main() {
	String *str1 = newStringWithCString("Hello World");
	String *str2 = newStringWithString(str1);

	printf("%s:%s\n", stringAsCString(str1), stringAsCString(str2));
	printf("Equals: %d\n", stringEquals(str1, str2));
}
