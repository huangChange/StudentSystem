#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <malloc.h>
#include <string>


#define Width 100		//��ʾ�ն˵Ŀ��
#define Height 30		//��ʾ�ն˵ĸ߶�
using namespace std;
typedef struct Student {

	char name[20];		//ѧ��������
	/*string name;*/
	int num;			//ѧ����ѧ��
	int math;			//ѧ������ѧ�ɼ�
	int chinese;		//ѧ�������ĳɼ�
	int English;		//ѧ����Ӣ��ɼ�
	double ave;			//ƽ���ɼ�
	//int count;			//ѧ���ĸ���
	struct Student *next;
}Student, Node;

Student *InitLink();

void menuShow() {


	string menu_manage[] = {

		"1.����ѧ������Ϣ",
		"2.����ѧ����Ϣ",
		"3.����ѧ����Ϣ",
		"4.��ӡѧ����Ϣ",
		"5.����ѧ����Ϣ",
		"6.ɾ��ѧ����Ϣ",
		"7.ͳ��ѧ������",
		"8.�޸�ѧ����Ϣ",
		"9.�˳�"
	};

	int len = sizeof(menu_manage) / sizeof(menu_manage[0]);
	int max = menu_manage[0].length();

	for (int i = 0; i < len; i++) {
		if (menu_manage[i].length() > max) {
			max = menu_manage[i].length();
		}
	}

	for (int i = 0; i < (Width - max) / 2 - 4; i++) {
		cout << " ";
	}

	cout << "---ѧ���ɼ�����ϵͳ---" << endl;
	int left = (Width - max) / 2;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < left; j++) {
			cout << " ";
		}
		cout << menu_manage[i] << endl;
	}
}
//ǰ�巨
void input_stu(Student* &L) {
	if (!L) {
		cout << "���ʧ��!" << endl;
		return;
	}
	char flag;
	//Student *last = NULL;
	while (1) {
		Node *node = new Node;	//ÿ���²���һ���ڵ���Ҫ�ٴη����ڴ�ռ�
		//last = L;	//�������һ���ڵ�Ϊͷ���
		//while (last->next) last = last->next;//�ж����һ���ڵ����һ���ڵ��Ƿ�Ϊ��
											//�����Ϊ�գ�����һ���ڵ�ĵ�ַ�������һ���ڵ�
		cout << "������ѧ������: ";
		cin >> node->name;
		cout << "������ѧ��ѧ��: ";
		cin >> node->num;
		cout << "������ѧ����ѧ: ";
		cin >> node->math;
		cout << "������ѧ������: ";
		cin >> node->chinese;
		cout << "������ѧ��Ӣ��: ";
		cin >> node->English;
		node->ave = (node->math + node->chinese + node->English) / 3;
		//1.ͷ�巨
		node->next = L->next;//�²���Ľڵ�ָ��ԭ��ͷ���ָ����һ���ڵ�ĵ�ַ
		L->next = node;//���½��нڵ�ָ����һ���ڵ�ָ���²���Ľڵ�ĵ�ַ
		//2.β�巨
		//node->next = NULL;//���²���Ľڵ�ָ����һ���ڵ�ָ���ָ��
		//last->next = node;//���һ�ڵ�ָ����һ���ڵ�ĵ�ַָ���¼���Ľڵ�
		cout << "�Ƿ��������?: ";
		cin >> flag;
		if (flag == 'n') break;
	}
	
}

void print_stu(Student* &L) {
	
	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	Student *p = NULL;
	p = L->next;
	while (p) {
		cout << "ѧ����Ϣ: ���� " << p->name << " ѧ�� " << p->num
			<< " ��ѧ " << p->math << " ���� " << p->chinese << " Ӣ�� " << p->English
			<< " ƽ�� " << p->ave << endl;
		p = p->next;
	}
	cout << endl;
}

void rsearch_stu(Student* &L) {

	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	int num = 0, index = 0;
	cout << "������ѧ����ѧ��: " << endl;
	cin >> num;
	Student *p = NULL;
	p = L->next;
	while (p) {
		if (num == p->num) {
			cout << "ѧ����Ϣ����: " << endl;
			cout << "ѧ����Ϣ: ���� " << p->name << " ѧ�� " << p->num
				<< " ��ѧ " << p->math << " ���� " << p->chinese << " Ӣ�� " << p->English
				<< " ƽ�� " << p->ave << endl;
			index++;
		}
		p = p->next;
	}
	if (!p && index == 0) {
		cout << "δ�ҵ���ѧ��!" << endl;
	}
}

void statistick_stu(Student* &L) {
	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	int count = 0;
	Student *p = NULL;
	p = L->next;
	while (p) {
		count++;
		p = p->next;
	}
	cout << "һ���� " << count << " ��ѧ��!" << endl;
}

void store_stu(Student* &L) {
	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	Student *p = NULL;
	FILE *file;
	file = fopen("SystemStudent.txt", "w");
	if (file == NULL) {
		cout << "�ļ���ʧ��!" << endl;
		exit(-1);
	}
	p = L->next;
	while (p) {
		fprintf_s(file, "����: %s ѧ��: %d ��ѧ: %d ����: %d Ӣ��: %d\n", p->name, p->num,
			p->math, p->chinese, p->English);
		p = p->next;
	}
	cout <<"������Ϣ�ɹ�!" << endl;
}

void modify_stu(Student* &L) {
	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	Student *p = NULL;
	p = L->next;	//�Ӽ���ĵ�һ���ڵ�λ�ÿ�ʼ
	int num;
	cout << "��������Ҫ�޸�ѧ����Ϣѧ��ѧ��: " << endl;
	cin >> num;
	while (p) {
		if (num == p->num) {
			cout << "������ѧ������: ";
			cin >> p->name;
			cout << "������ѧ��ѧ��: ";
			cin >> p->num;
			cout << "������ѧ����ѧ: ";
			cin >> p->math;
			cout << "������ѧ������: ";
			cin >> p->chinese;
			cout << "������ѧ��Ӣ��: ";
			cin >> p->English;
			p->ave = (p->math + p->chinese + p->English) / 3;
		}
		p = p->next;
		cout << "�޸ĳɹ�!" << endl;
	}
	if (!p) cout << "δ�ҵ���ѧ��!" << endl;
}

void insert_stu(Student* &L) {
	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	Student *p = NULL;
	p = L;	//��ͷ�ڵ�λ�ÿ�ʼ,��Ϊͷ���������Ϊ��
	int j = 0, pos = 0, num = 0;
	cout << "������Ҫ����ѧ���ĸ���: ";
	cin >> num;
	for (int i = 0; i < num; i++) {
		cout << "������� " << i + 1 << " ������ѧ����λ��: " << endl;
		cin >> pos;
		Node *node = new Node;
		while (p && j < pos - 1) {
			p = p->next;
			j++;
		}
		if (!p || pos <= 0) {
			cout << "��Ҫ����λ�ò�����!" << endl;
			return;
		}
		else {
			cout << "������ѧ������: ";
			cin >> node->name;
			cout << "������ѧ��ѧ��: ";
			cin >> node->num;
			cout << "������ѧ����ѧ: ";
			cin >> node->math;
			cout << "������ѧ������: ";
			cin >> node->chinese;
			cout << "������ѧ��Ӣ��: ";
			cin >> node->English;
			node->ave = (node->math + node->chinese + node->English) / 3;
			//p->nextָ����p�ڵ�ָ����һ���ڵ�  nodeΪ�²���Ľڵ�
			node->next = p->next;//�²���Ľڵ�ָ��Ҫ�����λ�õĽ��ָ����һ���ڵ�ĵ�ַ
			p->next = node;//���½�Ҫ(����λ�õĽڵ�ָ����һ���ڵ�ĵ�ַ)ָ���²���Ľڵ�ĵ�ַ
		}
		cout << "����ɹ�!" << endl;
	}
}

void delete_stu(Student* &L) {
	if (!L) {
		cout << "������Ϊ��!" << endl;
		return;
	}
	Student *p = NULL, *q = NULL;
	p = L;
	int num = 0, index = 0;
	cout << "��������Ҫɾ��ѧ����ѧ��: ";
	cin >> num;
	while (p && p->next) {
		if (num == p->next->num) {	//Ҫɾ��ĳѧ��Ҫ���ҵ���ѧ����ǰһ��λ��
			q = p->next;//Ȼ���ڶ���һ���ڵ�ָ���ѧ����ַ
			p->next = q->next;//Ȼ���ٽ���ѧ��ǰһ��λ�õ���һ���ڵ�ָ���ѧ����һ���ڵ��λ��
			q = NULL;
			delete q;
			cout << "ɾ���ɹ�!" << endl;
			index++;
		}
		p = p->next;
	}
	if (index == 0 ) cout << "δ�ҵ���ѧ��!" << endl;
}

void menu() {

	Student *header = InitLink();
	

	char n;
	cout << "����������ʵ�ֵĹ���: ";
	while (1) {

		cin >> n;
		if (cin.fail()) {
			cin.clear();
			cin.sync();			//c++�б�ʾ��ջ�����
			 //fflush(stdin);		//c�����б�ʾ��ջ�����
		}
		//int ret = cin.peek();		�鿴����������
		//cout << ret << endl;
		//fflush(stdin);
		switch (n) {
		case '1':
			input_stu(header);		//����ѧ����Ϣ
			break;
		case '2':
			insert_stu(header);		//����ѧ����Ϣ
			break;
		case '3':
			rsearch_stu(header);		//����ѧ����Ϣ
			break;
		case '4':
			print_stu(header);		//��ӡѧ����Ϣ
			break;
		case '5':
			store_stu(header);		//����ѧ����Ϣ
			break;
		case '6':
			delete_stu(header);			//ɾ��ѧ����Ϣ
			break;
		case '7':
			statistick_stu(header);	//ͳ��ѧ������
			break;
		case '8':
			modify_stu(header);		//�޸�ѧ����Ϣ
			break;
		case '9':
			exit(1);
		default:
			cout << "�����������������: \n";
			break;
		}
		system("pause");
		system("cls");
		menuShow();
		cout << "���ٴ�����: ";
	}
}
void init() {
	char cmd[64];
	sprintf_s(cmd, "mode con cols=%d lines=%d", Width, Height);
	system(cmd);
}

Student *InitLink() {
	Student *header = new Student;
	if (!header) {
		cout << "��ʼ��ʧ��!" << endl;
		return NULL;
	}
	//header->count = 0;
	header->next = NULL;
	return header;
}

int main(void) {
	

	//��ʼ��ͷ���
	InitLink();

	init();
	menuShow();
	menu();

	system("pause");
	return 0;
}