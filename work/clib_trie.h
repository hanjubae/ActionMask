#ifndef __D_TRIE_H__

#define __D_TRIE_H__
#define TRUE    1
#define FALSE   0

typedef struct node {
	struct node* child[26];
	int word;
}Node;

node* newNode();
void insert(Node* root, char* str);
int search(Node* root, char* str);
void showtree(node* now, char* str, int depth);
int remove(Node* now, char* str, int i);


#endif