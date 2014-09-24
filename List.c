#include <stdlib.h>
#include <assert.h>
#include "List.h"

List *newList() {
	List *l = calloc(1, sizeof(List));

	assert(l != NULL);

	return l;
}

void deleteList(List *list) {
	listClear(list);

	free(list);
}

void listClear(List *list) {
	for (ListNode *n = list->first; n != NULL; ) {
		ListNode *tmp = n;

		n = n->next;

		free(tmp);
	}
	list->first = list->last = NULL;

	list->size = 0;
}

static ListNode *newListNode() {
	ListNode *l = calloc(1, sizeof(ListNode));

	assert(l != NULL);

	return l;
}

void listAddLast(List *list, void *data) {
	ListNode *n = newListNode();

	if (list->last != NULL) {
		list->last->next = n;
		n->previous = list->last;
		if (list->first == list->last) {
			assert(list->size == 1);
		}
	} else {
		//List is empty
		assert(list->first == NULL);
		list->first = n;
	}

	list->last = n;
	n->data = data;
	list->size += 1;
}

void listAddFirst(List *list, void *data) {
	ListNode *n = newListNode();

	if (list->first != NULL) {
		list->first->previous = n;
		n->next = list->first;
		if (list->first == list->last) {
			assert(list->size == 1);
		}
	} else {
		//Empty list
		assert(list->last == NULL);
		list->last = n;
	}
	list->first = n;
	n->data = data;
	list->size += 1;
}

void listInsertAfter(List *list, ListNode *node, void *data) {
	ListNode *n = newListNode();

	if (list->last == NULL) {
		//Empty
		assert(list->first == NULL);
		list->first = list->last = n;
	} else if (list->last == node) {
		list->last = n;
	}
	n->previous = node;
	n->next = node->next;
	if (node->next != NULL) {
		node->next->previous = n;
	}
	node->next = n;
	n->data = data;
	list->size += 1;
}

void listInsertBefore(List *list, ListNode *node, void *data) {
	ListNode *n = newListNode();

	if (list->first == NULL) {
		//Empty
		assert(list->last == NULL);
		list->first = list->last = n;
	} else if (list->first == node) {
		list->first = n;
	}
	n->next = node;
	n->previous = node->previous;
	if (node->previous != NULL) {
		node->previous->next = n;
	}
	node->previous = n;
	n->data = data;
	list->size += 1;
}

void listRemove(List *list, void *data) {
	for (ListNode *n = list->first; n != NULL; n = n->next) {
		if (n->data == data) {
			listRemoveNode(list, n);
			return;
		}
	}
}

void listRemoveNode(List *list, ListNode *n) {
	assert(list->size > 0);

	if (n->previous != NULL) {
		n->previous->next = n->next;
	}
	if (n->next != NULL) {
		n->next->previous = n->previous;
	}
	if (list->first == n) {
		list->first = n->next;
	}
	if (list->last == n) {
		list->last = n->previous;
	}

	free(n);
	list->size -= 1;
}

void listRemoveFirst(List *list) {
	if (list->size == 0) {
		return;
	}
	assert(list->first != NULL);

	listRemoveNode(list, list->first);
}

void listRemoveLast(List *list) {
	if (list->size == 0) {
		return;
	}
	assert(list->last != NULL);

	listRemoveNode(list, list->last);
}
