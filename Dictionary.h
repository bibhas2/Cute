struct Node { /* table entry: */
    struct Node *next; /* next entry in chain */
    char *key; /* defined key */
    void *value; /* replacement text */
};

typedef struct _Dictionary {
        struct Node **buckets; /* pointer table */
	int numBuckets;
	unsigned (*hash_function)(struct _Dictionary *d, const char *s);
} Dictionary;

Dictionary* newDictionary();
Dictionary* newDictionaryWithSize(int bucketSize);
void deleteDictionary(Dictionary* d);
void *dictionaryGet(Dictionary *d, const char *s);
void dictionaryPut(Dictionary *d, const char *key, void *value);
void *dictionaryRemove(Dictionary *d, const char *key);
