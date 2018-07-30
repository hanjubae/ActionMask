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
	
	if (plist->head == NULL) {
		plist->head = newNode;
	}
	else {
		newNode->next = plist->head;
		plist->head = newNode;
	}
	plist->size++;
}

int remove(List* plist, char remove_name[]) {
	int ret = 0;
	
	Node* cur = plist->head;
	if (cur == NULL) return ret;
	if (strcomp(cur->data.name, remove_name) == 0) return 1;
	
	while (cur->next != NULL) {
		if (strcomp(cur->next->data.name, remove_name) == 0) {
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

Info search(List* plist, char find_name[]) {
	Info ret;
	Node* cur = plist->head;
	while (cur != NULL) {
		if (strcomp(cur->next->data.name, find_name) == 0) {
			strcpy(ret.name, cur->data.name);
			strcpy(ret.header, cur->data.header);
			strcpy(ret.prototype, cur->data.prototype);
			strcpy(ret.description, cur->data.description);

			return ret;
		}
		cur = cur->next;
	}
	
	return ret;
}

int size(List* plist) {
	return plist->size;
}

int main() {

	return 0;
}