#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "clib_list.h"
#include "clib_trie.h"

void clear(void)
{
	while (getchar() != '\n');
}

int main() {
	List list;
	trie_node* root = newNode();
	init(&list);

	FILE *fp = fopen("C_library.txt", "r");
	if (fp == NULL) {
		puts("Can't open library file");
		exit(0);
	}

	int flag = 0;
	while (flag != EOF) {
		Info data;
		flag = fscanf(fp, "%[^\t]s", data.name);

		fgetc(fp);
		if (flag != EOF) {
			fscanf(fp, "%[^\t]s", data.header);
			fgetc(fp);
			fscanf(fp, "%[^\t]s", data.prototype);
			fgetc(fp);
			fscanf(fp, "%[^\n]s", data.description);
			fgetc(fp);
			push(&list, data);

			insert(root, data.name);
		}
	}

	int push_check = 0;
	Info push_tmp = { '0', '0', '0', '0' }; // 삽입용 임시자료형
	char push_name[32] = { '0' };
	char push_header[32] = { '0' };
	char push_proto[160] = { '0' };
	char push_desc[200] = { '0' };
	char del_name[32] = { '0' };
	char sel[1];
	int prevState = 0;
	char c; // 받을 단어를 담는 변수
	Info* success;	// 검색 성공시 담을 그릇
	char find_name[32];	// 찾고자 하는 단어
	char temp_name[32];
	find_name[0] = 0;	// 찾고자 하는 단어 초기화
	int find_name_size = 0;	//찾고자 하는 단어 사이즈
	int count[1] = { 0 };	// 탭기능에서 연관단어 갯수

	while (1) {
		if (!prevState) {	//새로운 실행상태를 원할 경우
			sel[0] = -1;
			printf("무엇을 실행할 것인가 ?");
			scanf("%s", sel);
		}	
	
		switch (sel[0]) {
		case '1': {
			printf("찾고자 하는 함수명 ? : %s", find_name);
			// search
			clear();
			while (1) {
				c = getchar();
				//printf("입력한 값 : %d\n", c);
				if (c == '\t') { // tab 탐색
					printf("탭 인 !!\n");
					find_name[find_name_size] = 0;

					if (!lenCheck(push_name, sizeof(push_name)) || !wordCheck(push_name)) {
						printf("0~9사이의 숫자, 언더바(_), 알파벳 소문자만 입력해주세요.\n");
						find_name_size = 0;
						find_name[0] = 0;
					}

					count[0] = 0;
					countWord(root, find_name, count);
					printf("카운트 : %d\n", count[0]);
					if (count[0] == 0) {	//아무 변화 없이 그대로
						continue;
					}
					else if (count[0] == 1) {	//자동 완성
						printf("자동완성\n");
						strcpy(find_name, getRecommendOne(root, find_name));
						find_name_size = strlen(find_name);
						prevState = 1;
						break;
					}
					else {	// 연관 단어 검색
						printf("연관 단어 검색 \n");
						strcpy(temp_name, find_name);
						recommend(root, temp_name);
						prevState = 1;
						break;
					}
				}
				else if (c == '\n') {	//엔터 기본 search
					find_name[find_name_size] = '\0';
					if (find_name_size == 0) break;

					if (!lenCheck(push_name, sizeof(push_name)) || !wordCheck(push_name)) {
						printf("0~9사이의 숫자, 언더바(_), 알파벳 소문자만 입력해주세요.\n");
						find_name_size = 0;
						find_name[0] = 0;
					}

					success = search(&list, find_name);
					if (success == NULL) {
						printf("찾고자 하는 함수가 존재하지 않습니다.\n");
					}
					else {
						printf("%10s %10s %15s %20s\n", "함수명", "헤더 파일", "원 형", "설 명");
						printf("%10s %10s %15s %20s\n", success->name, success->header, success->prototype, success->description);
					}
					find_name_size = 0;
					find_name[0] = 0;
					prevState = 0;
					break;
				}
				else if((c >= 97 && c <= 122) || c == 95){
					find_name[find_name_size++] = c;
					prevState = 0;
				}
				else { //형식에 맞지 않는 문자
					printf("영어 소문자, 숫자, _만 기입하세요!!\n");
					find_name_size = 0;
					find_name[0] = 0;
					prevState = 1;
					break;
				}
			}


			break;
		}
		case '2': {
			// push
			while (1)
			{
				printf("2. 추가하고자 하는 함수명 : ");
				clear();
				scanf("%[^\n]s", push_name);
				if (search(&list, push_name) != NULL)
				{
					printf("이미 존재하는 함수입니다\n");
					push_check = 0;
					break;
				}
				if (lenCheck(push_name, sizeof(push_name)) == 0)
				{
					printf("%d글자 이내로 입력해 주세요.\n", sizeof(push_name));
				}
				if (wordCheck(push_name) == 0)
				{
					printf("0~9사이의 숫자, 언더바(_), 알파벳 소문자만 입력해주세요.\n");
				}
				if (lenCheck(push_name, sizeof(push_name)) && wordCheck(push_name)) {
					strcpy(push_tmp.name, push_name);
					push_check = 1;
					break;
				}
			}

			while (push_check)
			{
				printf("2-1.헤더를 입력하세요 : ");
				clear();
				scanf("%[^\n]s", push_header);
				if (lenCheck(push_header, sizeof(push_header)) == 0)
				{
					printf("%d글자 이내로 입력해 주세요.\n", sizeof(push_header));
				}
				else {
					strcpy(push_tmp.header, push_header);
					break;
				}
			}

			while (push_check)
			{
				printf("2-2.원형을 입력하세요 : ");
				clear();
				scanf("%[^\n]s", push_proto);
				if (lenCheck(push_proto, sizeof(push_proto)) == 0)
				{
					printf("%d글자 이내로 입력해 주세요.\n", sizeof(push_proto));
				}
				else {
					strcpy(push_tmp.prototype, push_proto);
					break;
				}
			}

			while (push_check)
			{
				printf("2-3.설명을 입력하세요 : ");
				clear();
				scanf("%[^\n]s", push_desc);
				if (lenCheck(push_desc, sizeof(push_desc)) == 0)
				{
					printf("%d글자 이내로 입력해 주세요.\n", sizeof(push_desc));
				}
				else {
					strcpy(push_tmp.description, push_desc);
					break;
				}
			}
			if (push_check)
			{
				push(&list, push_tmp);
				insert(root, push_tmp.name);
				printf("%s를 리스트에 삽입했습니다.\n", push_tmp.name);
				// 파일 갱신 함수
			}
			
			break;
		}
		case '3': {
			// remove
			printf("3. 삭제하고자 하는 함수는? : ");
			clear();
			scanf("%[^\n]s", del_name);
			
			success = search(&list, del_name);
			if (success != NULL)
			{
				remove(&list, del_name);
				trie_remove(root, del_name, strlen(del_name));
				printf("%s을(를) 삭제하였습니다.\n", del_name);
				// 파일 갱신 함수
				break;
			}
			else
			{
				printf("없는 함수입니다.\n");
				break;
			}
		}
		case '4': {
			// exit
			printf("프로그램을 종료합니다.\n");
			exit(1);
			break;
		}
		default: {
			printf("1~4만 입력하시오 !!!\n");
			break;
		}
		}
	}

	fclose(fp);
	return 0;
}