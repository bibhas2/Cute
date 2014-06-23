#include <stdio.h>
#include <assert.h>
#include "String.h"
#include "Dictionary.h"

String*
readLine(FILE *file, String *str) {
	if (str == NULL) {
		str = newString();
	} else {
		str->length = 0;
	}

	while (1) {
		int ch = fgetc(file);


		if (ch == '\r') {
			continue; //Eat
		}
		if (ch == '\n') {
			return str;
		}

		if (ch == EOF) {
			if (str->length > 0) {
				//File did not end with new line
				return str;
			} else {
				deleteString(str);

				return NULL;
			}
		}

		stringAppendChar(str, ch);
	}

	return str;
}

int
main() {
	FILE *file = fopen("/usr/share/dict/words", "r");

	assert(file != NULL);

	Dictionary *dict = newDictionary();
	String *str = NULL;

	while ((str = readLine(file, NULL)) != NULL) {
		dictionaryPut(dict,
			stringAsCString(str),
			str);
	}
	fclose(file);


	/*
	for (int i = 0; i < dict->numBuckets; ++i) {
		struct Node *n = dict->buckets[i];
		int count = 0;

		while (n != NULL) {
			n = n->next;
			++count;
		}
		printf("Bucket[%d]=%d\n", i, count);
	}
	*/

	String *value = NULL;

	puts("Please enter a lookup word. Empty input to quit.");
	while ((str = readLine(stdin, str)) != NULL) {
		if (str->length == 0) {
			break;
		}

		int removeWord = 0;
		const char *key = stringAsCString(str);

		if (str->buffer[0] == '-') {
			removeWord = 1;
			key = str->buffer + 1;
		}

		value = dictionaryGet(dict, key);
		if (value != NULL) {
			puts(stringAsCString(value));
		} else {
			puts("Not found.");
		}
		if (removeWord == 1) {
			dictionaryRemove(dict, key);
		}
	}

	deleteDictionary(dict);

	return 0;
}
