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
	Info push_tmp = { '0', '0', '0', '0' }; // ���Կ� �ӽ��ڷ���
	char push_name[32] = { '0' };
	char push_header[32] = { '0' };
	char push_proto[160] = { '0' };
	char push_desc[200] = { '0' };
	char del_name[32] = { '0' };
	char sel[1];
	int prevState = 0;
	char c; // ���� �ܾ ��� ����
	Info* success;	// �˻� ������ ���� �׸�
	char find_name[32];	// ã���� �ϴ� �ܾ�
	char temp_name[32];
	find_name[0] = 0;	// ã���� �ϴ� �ܾ� �ʱ�ȭ
	int find_name_size = 0;	//ã���� �ϴ� �ܾ� ������
	int count[1] = { 0 };	// �Ǳ�ɿ��� �����ܾ� ����

	while (1) {
		if (!prevState) {	//���ο� ������¸� ���� ���
			sel[0] = -1;
			printf("������ ������ ���ΰ� ?");
			scanf("%s", sel);
		}	
	
		switch (sel[0]) {
		case '1': {
			printf("ã���� �ϴ� �Լ��� ? : %s", find_name);
			// search
			clear();
			while (1) {
				c = getchar();
				//printf("�Է��� �� : %d\n", c);
				if (c == '\t') { // tab Ž��
					printf("�� �� !!\n");
					find_name[find_name_size] = 0;

					if (!lenCheck(push_name, sizeof(push_name)) || !wordCheck(push_name)) {
						printf("0~9������ ����, �����(_), ���ĺ� �ҹ��ڸ� �Է����ּ���.\n");
						find_name_size = 0;
						find_name[0] = 0;
					}

					count[0] = 0;
					countWord(root, find_name, count);
					printf("ī��Ʈ : %d\n", count[0]);
					if (count[0] == 0) {	//�ƹ� ��ȭ ���� �״��
						continue;
					}
					else if (count[0] == 1) {	//�ڵ� �ϼ�
						printf("�ڵ��ϼ�\n");
						strcpy(find_name, getRecommendOne(root, find_name));
						find_name_size = strlen(find_name);
						prevState = 1;
						break;
					}
					else {	// ���� �ܾ� �˻�
						printf("���� �ܾ� �˻� \n");
						strcpy(temp_name, find_name);
						recommend(root, temp_name);
						prevState = 1;
						break;
					}
				}
				else if (c == '\n') {	//���� �⺻ search
					find_name[find_name_size] = '\0';
					if (find_name_size == 0) break;

					if (!lenCheck(push_name, sizeof(push_name)) || !wordCheck(push_name)) {
						printf("0~9������ ����, �����(_), ���ĺ� �ҹ��ڸ� �Է����ּ���.\n");
						find_name_size = 0;
						find_name[0] = 0;
					}

					success = search(&list, find_name);
					if (success == NULL) {
						printf("ã���� �ϴ� �Լ��� �������� �ʽ��ϴ�.\n");
					}
					else {
						printf("%10s %10s %15s %20s\n", "�Լ���", "��� ����", "�� ��", "�� ��");
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
				else { //���Ŀ� ���� �ʴ� ����
					printf("���� �ҹ���, ����, _�� �����ϼ���!!\n");
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
				printf("2. �߰��ϰ��� �ϴ� �Լ��� : ");
				clear();
				scanf("%[^\n]s", push_name);
				if (search(&list, push_name) != NULL)
				{
					printf("�̹� �����ϴ� �Լ��Դϴ�\n");
					push_check = 0;
					break;
				}
				if (lenCheck(push_name, sizeof(push_name)) == 0)
				{
					printf("%d���� �̳��� �Է��� �ּ���.\n", sizeof(push_name));
				}
				if (wordCheck(push_name) == 0)
				{
					printf("0~9������ ����, �����(_), ���ĺ� �ҹ��ڸ� �Է����ּ���.\n");
				}
				if (lenCheck(push_name, sizeof(push_name)) && wordCheck(push_name)) {
					strcpy(push_tmp.name, push_name);
					push_check = 1;
					break;
				}
			}

			while (push_check)
			{
				printf("2-1.����� �Է��ϼ��� : ");
				clear();
				scanf("%[^\n]s", push_header);
				if (lenCheck(push_header, sizeof(push_header)) == 0)
				{
					printf("%d���� �̳��� �Է��� �ּ���.\n", sizeof(push_header));
				}
				else {
					strcpy(push_tmp.header, push_header);
					break;
				}
			}

			while (push_check)
			{
				printf("2-2.������ �Է��ϼ��� : ");
				clear();
				scanf("%[^\n]s", push_proto);
				if (lenCheck(push_proto, sizeof(push_proto)) == 0)
				{
					printf("%d���� �̳��� �Է��� �ּ���.\n", sizeof(push_proto));
				}
				else {
					strcpy(push_tmp.prototype, push_proto);
					break;
				}
			}

			while (push_check)
			{
				printf("2-3.������ �Է��ϼ��� : ");
				clear();
				scanf("%[^\n]s", push_desc);
				if (lenCheck(push_desc, sizeof(push_desc)) == 0)
				{
					printf("%d���� �̳��� �Է��� �ּ���.\n", sizeof(push_desc));
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
				printf("%s�� ����Ʈ�� �����߽��ϴ�.\n", push_tmp.name);
				// ���� ���� �Լ�
			}
			
			break;
		}
		case '3': {
			// remove
			printf("3. �����ϰ��� �ϴ� �Լ���? : ");
			clear();
			scanf("%[^\n]s", del_name);
			
			success = search(&list, del_name);
			if (success != NULL)
			{
				remove(&list, del_name);
				trie_remove(root, del_name, strlen(del_name));
				printf("%s��(��) �����Ͽ����ϴ�.\n", del_name);
				// ���� ���� �Լ�
				break;
			}
			else
			{
				printf("���� �Լ��Դϴ�.\n");
				break;
			}
		}
		case '4': {
			// exit
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
			break;
		}
		default: {
			printf("1~4�� �Է��Ͻÿ� !!!\n");
			break;
		}
		}
	}

	fclose(fp);
	return 0;
}