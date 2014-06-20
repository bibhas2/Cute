#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Dictionary.h"

/* hash: form hash value for string s */
unsigned hash(Dictionary *d, char *s)
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

	return d;
}

void
deleteDictionary(Dictionary* d) {
	for (int i = 0; i < d->numBuckets; ++i) {
		struct Node *n = d->buckets[i];
		while (n != NULL) {
			struct Node *next = n->next;
			free(n->key);
			free(n);
			n = next;
		}
	}
	free(d->buckets);
	free(d);
}

/* _dictNodeGet: look for s in buckets */
struct Node *_dictNodeGet(Dictionary *d, char *s)
{
    struct Node *np;
    for (np = d->buckets[hash(d, s)]; np != NULL; np = np->next)
        if (strcmp(s, np->key) == 0)
          return np; /* found */
    return NULL; /* not found */
}

void* dictionaryGet(Dictionary *d, char *s) {
	struct Node *n = _dictNodeGet(d, s);

	if (n == NULL) {
		return NULL;
	}

	return n->value;
}

/* install: put (key, value) in buckets */
void
dictionaryPut(Dictionary *d, char *key, void *value)
{
    struct Node *np;
    unsigned hashval;
    if ((np = _dictNodeGet(d, key)) == NULL) { /* not found */
        np = (struct Node *) malloc(sizeof(*np));
	assert(np != NULL);
        np->key = strdup(key);
	assert(np->key != NULL);

        hashval = hash(d, key);
        np->next = d->buckets[hashval];
        d->buckets[hashval] = np;
    } 

    np->value = value;
}