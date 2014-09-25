/*
 * A doubly linked list.
 */
typedef struct _ListNode {
	struct _ListNode *previous;
	struct _ListNode *next;
	void *data;
} ListNode;

typedef struct _List {
	ListNode *first;
	ListNode *last;
	size_t size;
} List;

List *newList();
void deleteList(List *list);
void listClear(List *list);
void listAddLast(List *list, void *data);
void listAddFirst(List *list, void *data);
void listInsertAfter(List *list, ListNode *node, void *data);
void listInsertBefore(List *list, ListNode *node, void *data);
void listRemove(List *list, void *data);
void listRemoveNode(List *list, ListNode *node);
void listRemoveFirst(List *list);
void listRemoveLast(List *list);
void listReverse(List *list);
