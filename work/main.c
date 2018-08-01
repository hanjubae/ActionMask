#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "clib_list.h"

int main() {
	List list;
	init(&list);

	FILE *fp = fopen("C_library.txt", "r");
	if (fp == NULL) {
		puts("Can't open library file");
		exit(0);
	}

	int flag = 0;
	while (flag != EOF) {
		Info data;
		flag = fscanf(fp, "%[^\t]s", &data.name);
		fgetc(fp);
		if (flag != EOF) {
			fscanf(fp, "%[^\t]s", &data.header);
			fgetc(fp);
			fscanf(fp, "%[^\t]s", &data.prototype);
			fgetc(fp);
			fscanf(fp, "%[^\n]s", &data.description);
			fgetc(fp);
			push(&list, data);
		}
	}
	display(&list);

	while (1) {
		int sel;
		int isTab = 0;
		if (isTab) {
			sel = 1;
		}
		else {
			printf("무엇을 실행할 것인가 ? : ");
			scanf("%d", &sel);
		}

		char c;
		Info* success;
		char find_name[32];
		int find_name_size = 0;
		switch (sel) {
		case 1: {
			printf("찾고자 하는 함수명 ? : ");
			// search
			getchar();
			while (find_name_size < 32) {
				scanf("%c", &c);
				if (c == '\t') { // tab 탐색
					find_name[find_name_size] = 0;
					isTab++;
					if (isTab == 1) {

					}
					else if (isTab == 2) {

					}
				}
				else if (c == '\n') {	//엔터 기본 search
					find_name[find_name_size] = '\0';
					if (find_name_size == 0) break;

					success = search(&list, find_name);
					if (success == NULL) {
						printf("찾고자 하는 함수가 존재하지 않습니다.\n");
					}
					else {
						printf("%10s %10s %15s %20s\n", "함수명", "헤더 파일", "원 형", "설 명");
						printf("%10s %10s %15s %20s\n", success->name, success->header, success->prototype, success->description);
					}
					find_name_size = 0;
					isTab = 0;
				}
				else {
					find_name[find_name_size++] = c;
					isTab = 0;
				}
			}


			break;
		}
		case 2: {
			// push
			break;
		}
		case 3: {
			// remove
			break;
		}
		case 4: {
			// exit
			break;
		}
		default: {

		}
		}
	}

	return 0;
}