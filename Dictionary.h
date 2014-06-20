struct Node { /* table entry: */
    struct Node *next; /* next entry in chain */
    char *key; /* defined key */
    void *value; /* replacement text */
};

typedef struct _Dictionary {
        struct Node **buckets; /* pointer table */
	int numBuckets;
} Dictionary;

Dictionary* newDictionary();
Dictionary* newDictionaryWithSize(int bucketSize);
void deleteDictionary(Dictionary* d);
void *dictionaryGet(Dictionary *d, char *s);
void dictionaryPut(Dictionary *d, char *key, void *value);
void *dictionaryRemove(Dictionary *d, char *key);
