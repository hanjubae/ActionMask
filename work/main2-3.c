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
			printf("������ ������ ���ΰ� ? : ");
			scanf("%d", &sel);
		}

		char c;
		int push_count = 0;
		int push_check = 0; // �Է°� ����. 0�̸� ���� 1�̸� �̻�
		Info* success;
		Info push_tmp = { '0', '0', '0', '0' }; // ���Կ� �ӽ��ڷ���
		char find_name[32] = { '0' };
		char push_header[32] = { '0' };
		char push_proto[160] = { '0' };
		char push_desc[200] = { '0' };
		int find_name_size = 0;

		switch (sel) {
		case 1: {
			printf("1. ã���� �ϴ� �Լ��� ? : ");
			// search
			getchar();
			while (find_name_size < 32) {
				scanf("%c", &c);
				if (c == '\t') { // tab Ž��
					find_name[find_name_size] = 0;
					isTab++;
					if (isTab == 1) {

					}
					else if (isTab == 2) {

					}
				}
				else if (c == '\n') {	//���� �⺻ search
					find_name[find_name_size] = '\0';
					if (find_name_size == 0) break;

					success = search(&list, find_name);
					if (success == NULL) {
						printf("ã���� �ϴ� �Լ��� �������� �ʽ��ϴ�.\n");
					}
					else {
						printf("%10s %10s %15s %20s\n", "�Լ���", "��� ����", "�� ��", "�� ��");
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
			printf("2. �߰��ϰ��� �ϴ� �Լ��� : ");
			getchar();
			find_name_size = 0;
			push_check = 0;
			while (find_name_size < sizeof(find_name))
			{
				scanf("%c", &c);
				if (c == '\n' && push_check == 1)
				{
					printf("0~9������ ����, �����(_), ���ĺ� �ҹ��ڸ� �Է����ּ���.\n");
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
						printf("�̹� �����ϴ� �Լ��Դϴ�\n");
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
				// �Է� ���� ����
				if (((int)c >= 48 && (int)c <= 57) || (int)c == 95 || ((int)c >= 97 && (int)c <= 122))
					push_check = 0;
				else
					push_check = 1;
			}
			if (push_count == 1)
			{
				printf("����� �Է��ϼ��� : ");
				while (find_name_size < sizeof(push_header)) //��� �Է�
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
				printf("������ �Է��ϼ��� : ");
				while (find_name_size < sizeof(push_proto)) // ���� �Է�
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
				printf("������ �Է��ϼ��� : "); // ���� �Է�
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
				printf("%s�� ����Ʈ�� �����߽��ϴ�.\n", push_tmp.name);
			}
			push_count = 0;
			break;
		}
		case 3: {
			// remove
			printf("3. �����ϰ��� �ϴ� �Լ���? : ");
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
						printf("���� �Լ��Դϴ�.\n");
						break;
					}
					else
					{
						remove(&list, find_name);
						printf("%s��(��) �����Ͽ����ϴ�.\n", find_name);
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
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
			break;
		}
		default: {
			printf("1~4�� �Է��� �ּ���.\n");
			break;
		}
		}
	}

	return 0;
}