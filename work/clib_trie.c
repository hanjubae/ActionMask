#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clib_trie.h"

Node* newNode() {
	Node* new = (Node*)malloc(sizeof(Node));
	new->word = 0;
	for (int i = 0; i < 26; ++i) new->child[i] = 0;
	return new;
}
void insert(Node* root, char* str) {
	int len = strlen(str);
	Node* now = root;

	for (int i = 0; i < len; ++i) {
		if (!now->child[str[i] - 'a']) now->child[str[i] - 'a'] = newNode();
		now = now->child[str[i] - 'a'];
	}
	now->word = 1;
}
int search(Node* root, char* str) {
	int len = strlen(str);
	Node* now = root;

	for (int i = 0; i < len; ++i) {
		if (!now->child[str[i]-'a']) return 0;
		now = now->child[str[i] - 'a'];
	}
	return now->word;
}
void showtree(Node* now, char* str, int depth) {
	if (now->word) printf("%s\n", str);

	for (int i = 0; i < 26; ++i) {
		if (now->child[i]) {
			str[depth] = i + 'a';
			str[depth + 1] = 0;
			showtree(now->child[i], str, depth + 1);
		}
	}
}

int remove(Node* now, char* str, int i) {
	if (i == strlen(str)) {
		int chk = 0;
		for (int i = 0; i < 26; ++i) {
			if (now->child[i]) chk = 1;
		}
		if (chk) return 0;
		return 1;
	}
}