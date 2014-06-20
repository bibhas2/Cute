#include <stdio.h>
#include "Dictionary.h"

int
main() {
	Dictionary *d = newDictionary();

	dictionaryPut(d, "one", "One - 1");
	dictionaryPut(d, "two", "Two - 2");

	char *val = dictionaryGet(d, "two");
	printf("Val %s\n", val);

	val = dictionaryGet(d, "one");
	printf("Val %s\n", val);

	val = dictionaryGet(d, "three");
	printf("Val %s\n", val);

	deleteDictionary(d);
}
