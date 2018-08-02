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

	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee,W XyyyyyyyW,   eee   eeeeeeeeeeeeeeeeeeeeeeW ,eeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeW, XyyyyyyyyyyW, DXK,u eeeeeeeeeeeeeeeee#     Geeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee9  XyyyyyyyyyyyyWu  5y ueeeeeeeeeeeee5   Ky5 Weeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  Xyyyyyyyyyyyy55XX5yK eeeeeeeeeeu   Wy5yy  eeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee KW5yy55555yyWWKKWWWyK eeeeeeE   uW55yy55, eeeeeeeeeeeeeeeGee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee 5uX5yu,uuuuKWWyyyyWW u9GeG,  uy55y5y5yyu eeeeeeeeeeeeeeee Ee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeEW    , uuK5XXXXXXXDDDzz#zXK,    KDX5yyy5yy5K eeeeeeeeeeeeeeee   e\n");
	printf("eeeeeeeeuyEeeeeeeeeeeeeeeeeeeeeX   ,KyXXDXXX55yy5XD##D5Wu   yK  ,yXy,u5X5yyy5K eeeeeeeeeeeeeeeeD , u\n");
	printf("eeeeeeee9         W#eeeeeeeee   W55yyyyyyyyyyy5X#DK       WX9#z#GX uXX,u5555K eeeeeeeeeeeeeeeee KuWu\n");
	printf("eeeeeeeeee  W55yWK,      ,y  uyyyyyyyyyyyyyy5X#5        eeeeeeeeuWez 5XXuuXW eeeeeeeeeeeeeeee# u55uX\n");
	printf("eeeeeeeeeeeE uy5yyy55555y ,Wy5XXXX555yyyyyyXz5       eeeeeeeeeGeeeKE9 X5X5, eeeeeeeeeeeeeeeD  KyyK e\n");
	printf("eeeeeeeeeeeee  K5yyyy5X5 Xyu ,WXXXz#9zX5y5XzK     EeeW      ueeGEGeee X5y5X #eeeeeeeeeeee   Kyyyy Ee\n");
	printf("eeeeeeeeeeeeeeE  W5y55X y  ze#        X#X5W     eey       ,   eeEEEGe D5yy5W  eeeeeeeee zE Wyyyyu ee\n");
	printf("eeeeeeeeeeeeeeeeu ,y5X  KeeeWWeeeeG5    ,y eeee9e    ueee  u,  eEEEee Xy5yy5yu eeeeeeee ee  WyyW eee\n");
	printf("eeeeeeeeeeeeeeeeee, KW eeE 5eeeeG5W5Deyee ueeeEe  , eeeee, uu  eEGee yX5yyyy5y  ,uu     uee ,yy Weee\n");
	printf("eeeeeeeeeeeeeeeeeeee  Gez eeee          e 9eEGe  ,u eeeG  ,,  ueeeE u55yyy5yW Deeeeeeey  Xee K, eeee\n");
	printf("eeeeeeeeeeeeeeeeeeeee ee eeez     GeD   e5DeEEe   ,          Geee  y55y55y5X 9eeEEEEEeee  eeG  eeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeee eeeeee  u eeeee , E  eeEee5          eeee  W5yKu,      eeEEEEEEEGez  ee 9eeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeee #eEEe# ,, eeeD    e, ,eeeeeeeeGGeeeeee   ,    uyXeeeeezeEEEEEEEEEee u zWeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeee eeGee          e9u55u 5eeeeeeeee#W     ,5EeeeeeeeGEEGGGEEEEEEEEEEe  zDeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeee  eeeee5   uEeee,y55y5yu           5GeeeeeeeEEEEEEEEEEEEEEEEEEEEEGe eeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeE   W#eeeee#K  Ky555y555yK    WeeeeeeeGEEEEEEEEEEEEEEEEEEEEEEEEEEezWeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeee            ,WyKu  y55yu  KzeeeeeGEEEEEEEEEEEEEEEEEEEEEGeeeEEEEEeee eeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeu  EeeeeeeeeeeeeeeeeD    KeeeeeGEEEEEEEEEEEEEEEEEEEEEEGeeeG9eeeeeee  eeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeee  GeeeeeGEEEEEEEEEEEEeeeKDeeeEEEEEEEEEEEEEEEEEEEEEEEEEeeeuu           eeeeeeeeeeeee\n");
	printf("eKeeeeeeeeeeeeeX eeGEEEEEEEEEEEEEGeeeeeeeeeeEEEEEEEEEEEEEEEEEEEEEEEGeeeeKKeee u5Xyy5W eeeeeeeeeeeeee\n");
	printf("   eeeeeeeeeee yeeEEEEEEEEEEEEEeeeeX,    XeeEEEEEEEEEEEEEEEEEEEEGeeeeW   eeeee  Wy5W eeeeeeeeeeeeeee\n");
	printf("z   eeeeeeeeeDyeGEEEEEEEEEEEEeeey  KyXXX5, eeEEEEEEEEEEEEEEEEeeee9     ,K Xeeee5 KW Eeeeeeeeeeeeeeee\n");
	printf("e    eeeeeeee eGEEEEEEEEEEEEee5 KXDXXXXXXXy eEEEEEEEEEEEEEeeeey  Keeeeez W  eeeee  9eeeeeeeeeeeeeeee\n");
	printf("ee  u       e eEEEEEEEEEEEEee uXXXXXXXXXXXX eEEEEEEEEEGeeee5   eeeeeeeee5 Xu Eeeeee,eeeeeeeeeeeeeeee\n");
	printf("eee  ,y5yy5 e eGEEEEEEEEEEee WXXXXXXXXXXXXy eEEEEEEGeeeKy, , Xeeeeeeeeeee D5W  eeeeKeeeeeeeeeeeeeeee\n");
	printf("eeeee  uyyyuK99eEEEEEEEEEEeuKXXXXXXXXXXXXD EeEEEeeeeK  ee 5 Eeeeeeeeeeeee z55yK ,eeXeeeeeeeeeeeeeeee\n");
	printf("eeeeeee  uyy e eeEEEEEEEEee XXXXXXXXXXXXXX eeeee#  ,eeee uK eeeeeeeeeeeee D5555yu   eeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeG  , Ee EeeEEEEEEe# DXXXXXXXXXXXD,EeeX  5eeeee  yX eeeeeeeeeeeeee X5555555Xu eeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeW  eeyKeeeGEEEe# DXXXXXXXXXX#W5eu EeeeeeX  u55X eeeeeeeeeeeeee D55XXDDXX5 eeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeee  D9   #eeeeeuzXXXXXXXDz#u ,KyW      ,W5555X eeeeeeeeeeeeeW #XD5u  uXD,Weeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeXeeeXKuu    zzzDzz#5, XDX555555DKXzXDXXXD eeeeeeeeeeeee    uWDzDD ,u eeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeu       uXXX55555XXDzu      uW eeeeeeeeeeeee ee    K,u   Xeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeee,ee zX55555XXDXu   yEEE#5,  Weeeeeeeeeee   ee9 XWEe#eeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeey  X5555XDXK   yee5 Dee#eeD eeeeeeeeeee W  ee WyK eWeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee K5XXDWuuW Xee#zeeeee  eeyeeeeeeeeeee 5y eeD 55W  eeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeu W,     ee ee9W  eee  ee eeeeeeeeee yy eee 5y55 eeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeey   DeEee  e     XeeE  e,eeeeeeeeee Wy Xee Xyy5W eeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee zeeee e5 ee#GeeEKeee eXeeeeeeeeeee u5 Dee 5yyy5 Weeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee eeeeeWe  ee  ,KK  #eee eeeeeeeeeee# 5 eeX 5y5yyW eeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee eeeu  eyEe9     y5eee ueeeeeeeeeeee W ee W5yyyyW eeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee E   K Keeeeeeeeeee9,  Eeeeeeeeeeeee  #eK yyyyy5  eeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee KKyyyWu  ,yD#DW    uy,Keeeeeeeeeeee ee  y5yyy5K eeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee WX5yyyyyWKu  ,uKWyyyyW eeeeeeeeeeee z uyyyy5Xy eeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee y X5yyyyyyyyyyyyyyyyyyu Keeeeeeeee WX5X5XXXD, #eeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee WXK ,yX5yyyyyyyyyyyyyyyyW  KGeeeez  uuWy5yK   eeeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee 55XD5u ,555yyyyyyyyyyyyyyyK,      Ky5yWKuu  zeeeeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeey 5yyy5XDy, KX55yyyyyyyyyyyyyyyyyyyyyyyy5W  ueeeeeeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee yyyy5yy55XDK  yX55yyyyyyyyyyyyyyyyyyK,   5eeeeeeeeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee Xyyyyyyyyy5XDXu  ,y55555555yyWKu     ,#eeeeeeeeeeeeeeeeeeeeeeeeee\n");
	printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee Xyyyyyyyyy5yy5XDD5uuuu          KXeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
	while (1) {
		if (!prevState) {	//새로운 실행상태를 원할 경우
			sel[0] = -1;
			printf("-----------------------------------\n");
			printf("1. 함수 검색\n");
			printf("2. 함수 추가\n");
			printf("3. 함수 삭제\n");
			printf("4. 프로그램 종료\n");
			printf("-----------------------------------\n");
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
