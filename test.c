#include <stdio.h>
#include "Dictionary.h"

int
print_all(const char* key, void *value) {
	printf("%s=%s\n", key, value);

	return 1;
}

int
main() {
	Dictionary *dict = newDictionary();
	
	dictionaryPut(dict, "US", "United States of America");
	dictionaryPut(dict, "CA", "Canada");

	dictionaryIterate(dict, print_all);

	return 0;
}
