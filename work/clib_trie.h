#ifndef __D_TRIE_H__

#define __D_TRIE_H__
#define TRUE    1
#define FALSE   0

typedef struct node {
	struct node* child[37];
	int word;
}trie_node;

trie_node* newNode();
void insert(trie_node* root, char* str);
int trie_search(trie_node* root, char* str);
void showtree(trie_node* now, char* str, int depth);
int trie_remove(trie_node* now, char* str, int i);
void recommend(trie_node* root, char* str);
void countWord(trie_node* root, char* str, int* ret);
char* getRecommendOne(trie_node* root, char* str);
void countTree(trie_node* now, int* ret);

#endif