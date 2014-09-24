#include <stdio.h>
#include "List.h"

void print_list(List *list) {
	puts("================");
	for (ListNode *n = list->first; n != NULL; n = n->next) {
		puts((const char*) n->data);
	}
}

int
main() {
	List *list = newList();

	listAddLast(list, "One");
	listAddLast(list, "Two");
	listAddLast(list, "Three");
	listAddFirst(list, "One");
	listAddFirst(list, "Two");
	listAddFirst(list, "Three");

	print_list(list);

	listRemoveFirst(list);
	print_list(list);
	listRemoveLast(list);
	print_list(list);

	listClear(list);
	listAddLast(list, "One");
	listRemoveFirst(list);
	print_list(list);

	listAddFirst(list, "One");
	listAddLast(list, "One");
	listAddFirst(list, "Two");
	listAddLast(list, "Two");
	listAddFirst(list, "Three");
	listAddLast(list, "Three");
	print_list(list);

	deleteList(list);

	return 0;
}
