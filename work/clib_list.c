#include <stdio.h>
#include <stdlib.h>
#include "clib_list.h"


void init(List* plist) {
	plist->head = NULL;
	plist->size = 0;
}
void push(List* plist, Info data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;

	if(plist->head == NULL) {
		plist->head = newNode;
	} else {
		newNode->next = plist->head;
		plist->head = newNode;
	}
	plist->size++;
}
int remove(List* plist, char remove_name[]) {
	int ret = 0;

	Node* cur = plist->head;
	if (cur == NULL) return ret;
	if(strcomp(cur->name, remove_name) == 0) return 1;

	while(cur->next != NULL) {
		if(strcomp(cur->next->name, remove_name) == 0) {
			Node* temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
			ret = 1;
			break;
		}

		cur = cur->next;
	}
	return ret;
}

Node search(List* plist, char find_name[]) {
	Node ret = NULL;

	Node* cur = plist->head;
	while(cur != NULL) {
		if(strcomp(cur->next->name, remove_name) == 0) {
			ret->name = cur->name;
			ret->header = cur->header;
			ret->prototype = cur->prototype;
			ret->description = cur->description;

			return ret;
		}

		cur = cur->next;
	}
	return ret;
	
}
int size(List* plist) {
	return plist->size;
}



