#include <stdio.h>
#include "String.h"

int
print_all(const char* key, void *value) {
	printf("%s=%s\n", key, value);

	return 1;
}

void print_string(String *str) {
	printf("[%.*s] - %zu\n", (int) str->length, str->buffer, str->length);
}

void test(const char *cstr1, const char *cstr2) {
	String *str1 = newStringWithCString(cstr1);
	String *str2 = newStringWithCString(cstr2);
	printf("Starts with: %s\n",
		stringStartsWithCString(str1, cstr2) ? "Y" : "N");
	deleteString(str1);
	deleteString(str2);
}

int
main() {
	test("ABCD", "AB");
	test("ABCD", "AC");
	test("AB", "ABCD");
	test("ABCD", "ABCD");
	test("ABCD", "");
	test("", "ABCD");
	test("", "");

	return 0;
}
