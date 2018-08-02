#ifndef __D_LINKED_LIST_H__

#define __D_LINKED_LIST_H__
#define TRUE    1
#define FALSE   0

typedef struct clib_info {
	char name[32];
	char header[32];
	char prototype[160];
	char description[200];
}Info;

typedef struct clib_node {
	Info data;
	struct clib_node* next;
}Node;

typedef struct clib_list {
	Node* head;
	int size;
}List;

void init(List* plist);
void push(List* plist, Info data);
int rmv(List* plist, char remove_name[]);
Info* search(List* plist, char find_name[]);
int size(List* plist);
void display(List* plist);
int wordCheck(char str[]);
int lenCheck(char str[], int max);
#endif
