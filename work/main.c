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
	
	printf("%c[1;37m",27);
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee 5uX5yu,uuuuKWWyyyyWW u9GeG,  uy55y5y5yyu eeeeeeeeeeeeeeee e\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeEW    , uuK5XXXXXXXDDDzz#zXK,    KDX5yyy5yy5K eeeeeeeeeeeeeeee  e\n");
	printf("eeeeeeeeuyEeeeeeeeeeeeeeeeeeeeeX   ,KyXXDXXX55yy5XD##D5Wu   yK  ,yXy,u5X5yyy5K eeeeeeeeeeeeeeeeD ,u\n");
	printf("eeeeeeee9         W#eeeeeeeee   W55yyyyyyyyyyy5X#DK       WX9#z#GX uXX,u5555K eeeeeeeeeeeeeeeee Kuu\n");
	printf("eeeeeeeeee  W55yWK,      ,y  uyyyyyyyyyyyyyy5X#5        eeeeeeeeuWez 5XXuuXW eeeeeeeeeeeeeeee# u55X\n");
	printf("eeeeeeeeeeeE uy5yyy55555y ,Wy5XXXX555yyyyyyXz5       eeeeeeeeeGeeeKE9 X5X5, eeeeeeeeeeeeeeeD  KyyKe\n");
	printf("eeeeeeeeeeeee  K5yyyy5X5 Xyu ,WXXXz#9zX5y5XzK     EeeW      ueeGEGeee X5y5X #eeeeeeeeeeee   Kyyyy e\n");
	printf("eeeeeeeeeeeeeeE  W5y55X y  ze#        X#X5W     eey       ,   eeEEEGe D5yy5W  eeeeeeeee zE Wyyyyu e\n");
	printf("eeeeeeeeeeeeeeeeu ,y5X  KeeeWWeeeeG5    ,y eeee9e    ueee  u,  eEEEee Xy5yy5yu eeeeeeee ee  WyyW ee\n");
	printf("eeeeeeeeeeeeeeeeee, KW eeE 5eeeeG5W5Deyee ueeeEe  , eeeee, uu  eEGee yX5yyyy5y  ,uu     uee ,yy Wee\n");
	printf("eeeeeeeeeeeeeeeeeeee  Gez eeee          e 9eEGe  ,u eeeG  ,,  ueeeE u55yyy5yW Deeeeeeey  Xee K, eee\n");
	printf("eeeeeeeeeeeeeeeeeeeee ee eeez     GeD   e5DeEEe   ,          Geee  y55y55y5X 9eeEEEEEeee  eeG  eeee\n");
	printf("eeeeeeeeeeeeeeeeeeeee eeeeee  u eeeee , E  eeEee5          eeee  W5yKu,      eeEEEEEEEGez  ee 9eeee\n");
	printf("eee ActionMask eeeeee #eEEe# ,, eeeD    e, ,eeeeeeeeGGeeeeee   ,    uyXeeeeezeEEEEEEEEEee u zWeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeee eeGee          e9u55u 5eeeeeeeee#W     ,5EeeeeeeeGEEGGGEEEEEEEEEEe  zDeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeee  eeeee5   uEeee,y55y5yu           5GeeeeeeeEEEEEEEEEEEEEEEEEEEEEGe eeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeE   W#eeeee#K  Ky555y555yK    WeeeeeeeGEEEEEEEEEEEEEEEEEEEEEEEEEEezWeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeee            ,WyKu  y55yu  KzeeeeeGEEEEEEEEEEEEEEEEEEEEEGeeeEEEEEeee eeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeu  EeeeeeeeeeeeeeeeeD    KeeeeeGEEEEEEEEEEEEEEEEEEEEEEGeeeG9eeeeeee  eeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeee  GeeeeeGEEEEEEEEEEEEeeeKDeeeEEEEEEEEEEEEEEEEEEEEEEEEEeeeuu           eeeeeeeeeeee\n");
	printf("eKeeeeeeeeeeeeeX eeGEEEEEEEEEEEEEGeeeeeeeeeeEEEEEEEEEEEEEEEEEEEEEEEGeeeeKKeee u5Xyy5W eeeeeeeeeeeee\n");
	printf("   eeeeeeeeeee yeeEEEEEEEEEEEEEeeeeX,    XeeEEEEEEEEEEEEEEEEEEEEGeeeeW   eeeee  Wy5W eeeeeeeeeeeeee\n");
	printf("z   eeeeeeeeeDyeGEEEEEEEEEEEEeeey  KyXXX5, eeEEEEEEEEEEEEEEEEeeee9     ,K Xeeee5 KW Eeeeeeeeeeeeeee\n");
	printf("e    eeeeeeee eGEEEEEEEEEEEEee5 KXDXXXXXXXy eEEEEEEEEEEEEEeeeey  Keeeeez W  eeeee  9eeeeeeeeeeeeeee\n");
	printf("ee  u       e eEEEEEEEEEEEEee uXXXXXXXXXXXX eEEEEEEEEEGeeee5   eeeeeeeee5 Xu Eeeeee,eeeeeeeeeeeeeee\n");
	printf("eee  ,y5yy5 e eGEEEEEEEEEEee WXXXXXXXXXXXXy eEEEEEEGeeeKy, , Xeeeeeeeeeee D5W  eeeeKeeeeeeeeeeeeeee\n");
	printf("eeeee  uyyyuK99eEEEEEEEEEEeuKXXXXXXXXXXXXD EeEEEeeeeK  ee 5 Eeeeeeeeeeeee z55yK ,eeXeeeeeeeeeeeeeee\n");
	printf("eeeeeee  uyy e eeEEEEEEEEee XXXXXXXXXXXXXX eeeee#  ,eeee uK eeeeeeeeeeeee D5555yu   eeeeeeeeeeeeeee\n");
	printf("eeeeeeeeG  , Ee EeeEEEEEEe# DXXXXXXXXXXXD,EeeX  5eeeee  yX eeeeeeeeeeeeee X5555555Xu eeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeW  eeyKeeeGEEEe# DXXXXXXXXXX#W5eu EeeeeeX  u55X eeeeeeeeeeeeee D55XXDDXX5 eeeeeeeeeeeeee\n");
	printf("%c[0m\n",27);
	
	while (1) {
		if (!prevState) {	//새로운 실행상태를 원할 경우
			sel[0] = -1;
			printf("%c[1;33m",27);
			printf("* * * * * * * * * * * * * * * * * * C 라이브러리  함수 도우미 * * * * * * * * * * * * * * * * * * *\n");
			printf("*\t\t\t\t\t\t\t\t\t\t\t\t  *\n");
			printf("*\t\t\t\t     ");
			printf("%c[1;37m",27);
			printf("1. 함	 수   ");
			printf("%c[1;33m",27);
			printf("검  색\t\t\t\t\t  *\n");

			printf("*\t\t\t\t     ");
			printf("%c[1;37m",27);
			printf("2. 함	 수   ");
			printf("%c[1;33m",27);
			printf("추  가\t\t\t\t\t  *\n");
			
			printf("*\t\t\t\t     ");
			printf("%c[1;37m",27);
			printf("3. 함	 수   ");
			printf("%c[1;33m",27);
			printf("삭  제\t\t\t\t\t  *\n");

			printf("*\t\t\t\t     ");
			printf("%c[1;37m",27);
			printf("4. 프 로 그 램   ");
			printf("%c[1;33m",27);
			printf("종  료\t\t\t\t\t  *\n");
			printf("*\t\t\t\t\t\t\t\t\t\t\t\t  *\n");
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			printf("\n");
			printf("%c[1;30m",27);
			printf(">>>>");
			printf("%c[1;37m",27);
			printf("실행 하고자 하는 기능의 ");
			printf("%c[1;31m",27);
			printf("번호");
			printf("%c[1;37m",27);
			printf("를 입력하고 ");
			printf("%c[1;31m",27);
			printf("ENTER");
			printf("%c[1;37m",27);
			printf("를 입력하여 주세요:");
			printf("%c[0m",27);
			scanf("%s", sel);
		}	
	
		switch (sel[0]) {
		case '1': {
			printf("%c[1;30m",27);
			printf(">>>>");						  
			printf("%c[1;37m",27);
			printf("찾고자 하는 ");
			printf("%c[1;31m",27);
			printf("함수");
			printf("%c[1;37m",27);
			printf("명 ? :");
			printf("%c[0m",27);
			printf("%s", find_name);
			// search
			clear();
			while (1) {
				c = getchar();
				//printf("입력한 값 : %d\n", c);
				if (c == '\t') { // tab 탐색
					find_name[find_name_size] = 0;

					if (!lenCheck(push_name, sizeof(push_name)) || !wordCheck(push_name)) {
						printf("0~9사이의 숫자, 언더바(_), 알파벳 소문자만 입력해주세요.\n");
						find_name_size = 0;
						find_name[0] = 0;
					}

					count[0] = 0;
					countWord(root, find_name, count);
					if (count[0] == 0) {	//아무 변화 없이 그대로
						continue;
					}
					else if (count[0] == 1) {	//자동 완성
						strcpy(find_name, getRecommendOne(root, find_name));
						find_name_size = strlen(find_name);
						prevState = 1;
						break;
					}
					else {	// 연관 단어 검색
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
						printf("함 수 명 : %s\n", success->name);
						printf("헤더파일 : %s\n", success->header);
						printf("원    형 : %s\n", success->prototype);
						printf("설    명 : %s\n", success->description);
					}
					find_name_size = 0;
					find_name[0] = 0;
					prevState = 0;
					break;
				}
				else if((c >= 97 && c <= 122) || c == 95 || (c >= 48 && c <= 57)){
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
				printf("%c[1;30m",27);
				printf(">>>>");						  
				printf("%c[1;37m",27);
				printf("2. 추가하고자 하는 ");
				printf("%c[1;31m",27);
				printf("함수");
				printf("%c[1;37m",27);
				printf("명 ? :");
				printf("%c[1;30m",27);
				printf("%c[0m",27);
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
			printf("%c[1;30m",27);
			printf(">>>>");						  
			printf("%c[1;37m",27);
			printf("3. 삭제하고자 하는 ");
			printf("%c[1;31m",27);
			printf("함수");
			printf("%c[1;37m",27);
			printf("는 ? :");
			printf("%c[1;30m",27);
			printf("%c[0m",27);
			clear();
			scanf("%[^\n]s", del_name);
			
			success = search(&list, del_name);
			if (success != NULL)
			{
				rmv(&list, del_name);
				trie_remove(root, del_name, strlen(del_name));
				printf("%s을(를) 삭제하였습니다.\n", del_name);
				// 파일 갱신 함수
				break;
			}
			else
			{
				printf("%s는 없는 함수입니다.\n", del_name);
				break;
			}
		}
		case '4': {
			// exit
			printf("%c[1;30m",27);
			printf(">>>>");						  
			printf("%c[1;37m",27);
			printf("4. 프로그램을  ");
			printf("%c[1;31m",27);
			printf("종료");
			printf("%c[1;37m",27);
			printf("합니다!");
			printf("%c[1;31m",27);
			printf("\nby ActionMask");
			printf("%c[0m\n",27);
			exit(1);
			break;
		}
		default: {
			printf("%c[1;30m",27);
			printf(">>>>>>>>>");						  
			printf("%c[1;31m",27);
			printf("1");
			printf("%c[1;37m",27);
			printf(" ~ ");
			printf("%c[1;31m",27);
			printf("4");
			printf("%c[1;37m",27);
			printf("만 입력해주세요 !!!\n");
			printf("%c[0m\n",27);
			break;
		}
		}
	}

	fclose(fp);
	return 0;
}
