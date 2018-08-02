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
		int push_count = 0;
		int push_check = 0; // 입력값 제한. 0이면 정상 1이면 이상
		Info* success;
		Info push_tmp = { '0', '0', '0', '0' }; // 삽입용 임시자료형
		char find_name[32] = { '0' };
		char push_header[32] = { '0' };
		char push_proto[160] = { '0' };
		char push_desc[200] = { '0' };
		int find_name_size = 0;

		switch (sel) {
		case 1: {
			printf("1. 찾고자 하는 함수명 ? : ");
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
			printf("2. 추가하고자 하는 함수명 : ");
			getchar();
			find_name_size = 0;
			push_check = 0;
			while (find_name_size < sizeof(find_name))
			{
				scanf("%c", &c);
				if (c == '\n' && push_check == 1)
				{
					printf("0~9사이의 숫자, 언더바(_), 알파벳 소문자만 입력해주세요.\n");
					push_check = 0;
					break;
				}
				else if (c == '\n' && push_check == 0)
				{
					find_name[find_name_size] = '\0';
					if (find_name_size == 0)
						break;
					success = search(&list, find_name);
					if (success != NULL)
					{
						printf("이미 존재하는 함수입니다\n");
						break;
					}
					else
					{
						strcpy(push_tmp.name, find_name);
						push_count = 1;
						find_name_size = 0;
						break;
					}
				}
				else
				{
					find_name[find_name_size++] = c;
				}
				// 입력 문자 제한
				if (((int)c >= 48 && (int)c <= 57) || (int)c == 95 || ((int)c >= 97 && (int)c <= 122))
					push_check = 0;
				else
					push_check = 1;
			}
			if (push_count == 1)
			{
				printf("헤더를 입력하세요 : ");
				while (find_name_size < sizeof(push_header)) //헤더 입력
				{
					scanf("%c", &c);
					if (c == '\n')
					{
						push_header[find_name_size] = '\0';
						strcpy(push_tmp.header, push_header);
						find_name_size = 0;
						break;
					}
					else
					{
						push_header[find_name_size++] = c;
					}
				}
				printf("원형을 입력하세요 : ");
				while (find_name_size < sizeof(push_proto)) // 원형 입력
				{
					scanf("%c", &c);
					if (c == '\n')
					{
						push_proto[find_name_size] = '\0';
						strcpy(push_tmp.prototype, push_proto);
						find_name_size = 0;
						break;
					}
					else
					{
						push_proto[find_name_size++] = c;
					}
				}
				printf("설명을 입력하세요 : "); // 설명 입력
				while (find_name_size < sizeof(push_desc))
				{
					scanf("%c", &c);
					if (c == '\n')
					{
						push_desc[find_name_size] = '\0';
						strcpy(push_tmp.description, push_desc);
						find_name_size = 0;
						break;
					}
					else
					{
						push_desc[find_name_size++] = c;
					}
				}
				push(&list, push_tmp);
				printf("%s를 리스트에 삽입했습니다.\n", push_tmp.name);
			}
			push_count = 0;
			break;
		}
		case 3: {
			// remove
			printf("3. 삭제하고자 하는 함수는? : ");
			getchar();
			find_name_size = 0;
			while (find_name_size < sizeof(find_name))
			{
				scanf("%c", &c);
				if (c == '\n')
				{
					find_name[find_name_size] = '\0';
					if (find_name_size == 0)
						break;
					success = search(&list, find_name);
					if (success == NULL)
					{
						printf("없는 함수입니다.\n");
						break;
					}
					else
					{
						remove(&list, find_name);
						printf("%s을(를) 삭제하였습니다.\n", find_name);
					}
					find_name_size = 0;
				}
				else
				{
					find_name[find_name_size++] = c;
				}
			}
			break;
		}
		case 4: {
			// exit
			printf("프로그램을 종료합니다.\n");
			exit(1);
			break;
		}
		default: {
			printf("1~4를 입력해 주세요.\n");
			break;
		}
		}
	}

	return 0;
}