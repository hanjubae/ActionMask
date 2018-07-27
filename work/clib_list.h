#include <stdio.h>

typedef struct clib_node{
	char[20] name;
	char[20] header;
	char[100] prototype;
	char[200] description;

	struct clib_node* next;
}node;

typedef struct clib_list {
	node head;
	int size;
}list;

void push(list& li, char name[], char header[], char prototype[], char description[]);
void pop(list& li);
int search(list& li, char find_name[]);



