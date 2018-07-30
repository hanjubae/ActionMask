#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#define TRUE	1
#define FALSE	0

typedef struct clib_info {	
	char[32] name;
	char[32] header;
	char[160] prototype;
	char[200] description;
}Info;

typedef struct clib_node {
	Info data;
	struct clib_node* next;
}Node;

typedef struct clib_list {
	Node head;
	int size;
}List;

void init(List* plist);
void push(List* plist, Info data);
void remove(List* plist, char remove_name[]);
Node search(List* plist, char find_name[]);
int size(List* plist);
#endif

