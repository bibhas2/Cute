#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Dictionary.h"

/* hash: form hash value for string s */
unsigned default_hash_function(Dictionary *d, const char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % d->numBuckets;
}

Dictionary*
newDictionary() {
	return newDictionaryWithSize(101);
}

Dictionary*
newDictionaryWithSize(int bucketSize) {
	Dictionary *d = malloc(sizeof(Dictionary));

	d->buckets = calloc(bucketSize, sizeof(struct Node*));
	d->numBuckets = bucketSize;
	d->hash_function = default_hash_function;

	return d;
}

void
dictionaryClear(Dictionary* d) {
	for (int i = 0; i < d->numBuckets; ++i) {
		struct Node *n = d->buckets[i];
		while (n != NULL) {
			struct Node *next = n->next;
			free(n->key);
			free(n);
			n = next;
		}
		d->buckets[i] = NULL;
	}
}

void
deleteDictionary(Dictionary* d) {
	dictionaryClear(d);

	free(d->buckets);
	free(d);
}

/* _dictNodeGet: look for s in buckets */
struct Node *_dictNodeGet(Dictionary *d, const char *s)
{
    struct Node *np;
    for (np = d->buckets[d->hash_function(d, s)]; np != NULL; np = np->next)
        if (strcmp(s, np->key) == 0)
          return np; /* found */
    return NULL; /* not found */
}

void *dictionaryRemove(Dictionary *d, const char *key)
{
	struct Node *np, *prev = NULL;
	unsigned index = d->hash_function(d, key);

	for (np = d->buckets[index]; np != NULL; np = np->next) {
		if (strcmp(key, np->key) == 0) {
			if (prev == NULL) {
				d->buckets[index] = np->next;
			} else {
				prev->next = np->next;

			}
			void *value = np->value;
			free(np->key);
			free(np);

			return value;	
		}
		prev = np;
	}

	return NULL; /* not found */
}

void* dictionaryGet(Dictionary *d, const char *s) {
	struct Node *n = _dictNodeGet(d, s);

	if (n == NULL) {
		return NULL;
	}

	return n->value;
}

/* install: put (key, value) in buckets */
void
dictionaryPut(Dictionary *d, const char *key, void *value)
{
    struct Node *np;
    unsigned hashval;
    if ((np = _dictNodeGet(d, key)) == NULL) { /* not found */
        np = (struct Node *) malloc(sizeof(*np));
	assert(np != NULL);
        np->key = strdup(key);
	assert(np->key != NULL);

        hashval = d->hash_function(d, key);
        np->next = d->buckets[hashval];
        d->buckets[hashval] = np;
    } 

    np->value = value;
}

void 
dictionaryIterate(Dictionary* dict, 
	int (*iterate_function)(const char *key, void *value)) {

        for (int i = 0; i < dict->numBuckets; ++i) {
                struct Node *n = dict->buckets[i];

                while (n != NULL) {
			int ret = iterate_function(n->key, n->value);
			if (ret == 0) {
				return;
			}
                        n = n->next;
                }
        }
}
