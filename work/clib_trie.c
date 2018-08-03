#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clib_trie.h"

trie_node* newNode() {
	trie_node* new = (trie_node*)malloc(sizeof(trie_node));
	new->word = 0;
	for (int i = 0; i < 37; ++i) new->child[i] = 0;
	return new;
}
void insert(trie_node* root, char* str) {
	int len = 0;
	while (str[len] != 0) {
		len++;
	}
	trie_node* now = root;

	for (int i = 0; i<len; i++) {
		int pos = str[i];
		if (pos >= 48 && pos <= 57) {
			pos = pos - '0';
		}
		else if(pos >= 97 && pos <= 122) {
			pos = pos - 'a' + 10;
		}
		else {
			pos = 36;
		}
		if (!(now->child[pos])) {
			now->child[pos] = newNode();
		}
		now = now->child[pos];
	}
	now->word = 1;
}
int trie_search(trie_node* root, char* str) {
	int len = strlen(str);
	trie_node* now = root;

	for (int i = 0; i<len; i++) {
		if (!now->child[str[i] - 'a']) return 0;
		now = now->child[str[i] - 'a'];
	}
	return now->word;
}
void showtree(trie_node* now, char* str, int depth) {
	if (now->word) printf("%s\n", str);

	for (int i = 0; i<37; i++) {
		if (now->child[i]) {
			if (i < 10) {
				str[depth] = i + '0';
				str[depth + 1] = 0;
			}
			else if (i >= 10 && i <= 35) {
				str[depth] = i + 'a' - 10;
				str[depth + 1] = 0;
			}
			else {
				str[depth] = '_';
				str[depth + 1] = 0;
			}
			
			
			showtree(now->child[i], str, depth + 1);
		}
	}
}

int trie_remove(trie_node* now, char* str, int i) {
	if (i == strlen(str)) {
		int chk = 0;
		for (int i = 0; i<37; i++) {
			if (now->child[i]) chk = 1;
		}
		if (chk) return 0;
		return 1;
	}

	int pos = str[i];

	if (pos >= 48 && pos <= 57) {
		pos = pos - '0';
	}
	else if (pos >= 97 && pos <= 122) {
		pos = pos - 'a' + 10;
	}
	else {
		pos = 36;
	}

	if (now->child[pos]) {
		if (trie_remove(now->child[pos], str, i + 1)) {
			free(now->child[pos]);
			now->child[pos] = 0;

			int chk = 0;
			for (int i = 0; i<37; i++) {
				if (now->child[i]) chk = 1;
			}

			if (chk) return 0;
			return 1;
		}
	}
	return 0;
}

void countWord(trie_node* root, char* str, int* ret) {
	int len = strlen(str);

	trie_node* now = root;

	for (int i = 0; i<len; i++) {
		int pos = str[i];

		if (pos >= 48 && pos <= 57) {
			pos = pos - '0';
		}
		else if (pos >= 97 && pos <= 122) {
			pos = pos - 'a' + 10;
		}
		else {
			pos = 36;
		}
		if (!now->child[pos]) return;
		now = now->child[pos];
	}

	countTree(now, ret);
}

void recommend(trie_node* root, char* str) {
	int len = strlen(str);

	trie_node* now = root;
	
	for (int i = 0; i<len; i++) {
		int pos = str[i];

		if (pos >= 48 && pos <= 57) {
			pos = pos - '0';
		}
		else if (pos >= 97 && pos <= 122) {
			pos = pos - 'a' + 10;
		}
		else {
			pos = 36;
		}
		if (!now->child[pos]) return;
		now = now->child[pos];
	}

	showtree(now, str, len);
}

char* getRecommendOne(trie_node* root, char* str) {
	int len = strlen(str);

	trie_node* now = root;

	for (int i = 0; i<len; i++) {
		int pos = str[i];

		if (pos >= 48 && pos <= 57) {
			pos = pos - '0';
		}
		else if (pos >= 97 && pos <= 122) {
			pos = pos - 'a' + 10;
		}
		else {
			pos = 36;
		}
		if (!now->child[pos]) return 0;
		now = now->child[pos];
	}

	while (1) {
		if (now->word) return str;

		for (int i = 0; i<37; i++) {
			if (now->child[i]) {
				if (i < 10) {
					str[len] = i + '0';
					str[len + 1] = 0;
				}
				else if (i >= 10 && i <= 35) {
					str[len] = i + 'a' - 10;
					str[len + 1] = 0;
				}
				else {
					str[len] = '_';
					str[len + 1] = 0;
				}

				now = now->child[i];
				len = len + 1;
				break;
			}
		}
	}
	
}

void countTree(trie_node* now, int* ret) {
	if (now->word) {
		ret[0]++;
	}

	for (int i = 0; i<37; i++) {
		if (now->child[i]) {
			countTree(now->child[i], ret);
		}
	}
}
