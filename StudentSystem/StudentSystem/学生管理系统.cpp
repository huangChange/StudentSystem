#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <malloc.h>
#include <string>


#define Width 100		//表示终端的宽度
#define Height 30		//表示终端的高度
using namespace std;
typedef struct Student {

	char name[20];		//学生的姓名
	/*string name;*/
	int num;			//学生的学号
	int math;			//学生的数学成绩
	int chinese;		//学生的语文成绩
	int English;		//学生的英语成绩
	double ave;			//平均成绩
	//int count;			//学生的个数
	struct Student *next;
}Student, Node;

Student *InitLink();

void menuShow() {


	string menu_manage[] = {

		"1.输入学生的信息",
		"2.插入学生信息",
		"3.查找学生信息",
		"4.打印学生信息",
		"5.保存学生信息",
		"6.删除学生信息",
		"7.统计学生人数",
		"8.修改学生信息",
		"9.退出"
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

	cout << "---学生成绩管理系统---" << endl;
	int left = (Width - max) / 2;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < left; j++) {
			cout << " ";
		}
		cout << menu_manage[i] << endl;
	}
}
//前插法
void input_stu(Student* &L) {
	if (!L) {
		cout << "添加失败!" << endl;
		return;
	}
	char flag;
	//Student *last = NULL;
	while (1) {
		Node *node = new Node;	//每次新插入一个节点需要再次分配内存空间
		//last = L;	//假设最后一个节点为头结点
		//while (last->next) last = last->next;//判断最后一个节点的下一个节点是否为空
											//如果不为空，则将下一个节点的地址赋给最后一个节点
		cout << "请输入学生姓名: ";
		cin >> node->name;
		cout << "请输入学生学号: ";
		cin >> node->num;
		cout << "请输入学生数学: ";
		cin >> node->math;
		cout << "请输入学生语文: ";
		cin >> node->chinese;
		cout << "请输入学生英语: ";
		cin >> node->English;
		node->ave = (node->math + node->chinese + node->English) / 3;
		//1.头插法
		node->next = L->next;//新插入的节点指向原先头结点指向下一个节点的地址
		L->next = node;//重新将有节点指向下一个节点指向新插入的节点的地址
		//2.尾插法
		//node->next = NULL;//将新插入的节点指向下一个节点指向空指针
		//last->next = node;//最后一节点指向下一个节点的地址指向新加入的节点
		cout << "是否继续输入?: ";
		cin >> flag;
		if (flag == 'n') break;
	}
	
}

void print_stu(Student* &L) {
	
	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	Student *p = NULL;
	p = L->next;
	while (p) {
		cout << "学生信息: 姓名 " << p->name << " 学号 " << p->num
			<< " 数学 " << p->math << " 语文 " << p->chinese << " 英语 " << p->English
			<< " 平均 " << p->ave << endl;
		p = p->next;
	}
	cout << endl;
}

void rsearch_stu(Student* &L) {

	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	int num = 0, index = 0;
	cout << "请输入学生的学号: " << endl;
	cin >> num;
	Student *p = NULL;
	p = L->next;
	while (p) {
		if (num == p->num) {
			cout << "学生信息如下: " << endl;
			cout << "学生信息: 姓名 " << p->name << " 学号 " << p->num
				<< " 数学 " << p->math << " 语文 " << p->chinese << " 英语 " << p->English
				<< " 平均 " << p->ave << endl;
			index++;
		}
		p = p->next;
	}
	if (!p && index == 0) {
		cout << "未找到此学生!" << endl;
	}
}

void statistick_stu(Student* &L) {
	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	int count = 0;
	Student *p = NULL;
	p = L->next;
	while (p) {
		count++;
		p = p->next;
	}
	cout << "一共有 " << count << " 个学生!" << endl;
}

void store_stu(Student* &L) {
	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	Student *p = NULL;
	FILE *file;
	file = fopen("SystemStudent.txt", "w");
	if (file == NULL) {
		cout << "文件打开失败!" << endl;
		exit(-1);
	}
	p = L->next;
	while (p) {
		fprintf_s(file, "姓名: %s 学号: %d 数学: %d 语文: %d 英语: %d\n", p->name, p->num,
			p->math, p->chinese, p->English);
		p = p->next;
	}
	cout <<"保存信息成功!" << endl;
}

void modify_stu(Student* &L) {
	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	Student *p = NULL;
	p = L->next;	//从加入的第一个节点位置开始
	int num;
	cout << "请输入你要修改学生信息学生学号: " << endl;
	cin >> num;
	while (p) {
		if (num == p->num) {
			cout << "请输入学生姓名: ";
			cin >> p->name;
			cout << "请输入学生学号: ";
			cin >> p->num;
			cout << "请输入学生数学: ";
			cin >> p->math;
			cout << "请输入学生语文: ";
			cin >> p->chinese;
			cout << "请输入学生英语: ";
			cin >> p->English;
			p->ave = (p->math + p->chinese + p->English) / 3;
		}
		p = p->next;
		cout << "修改成功!" << endl;
	}
	if (!p) cout << "未找到此学生!" << endl;
}

void insert_stu(Student* &L) {
	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	Student *p = NULL;
	p = L;	//从头节点位置开始,因为头结点数据域为空
	int j = 0, pos = 0, num = 0;
	cout << "请输入要插入学生的个数: ";
	cin >> num;
	for (int i = 0; i < num; i++) {
		cout << "请输入第 " << i + 1 << " 个插入学生的位置: " << endl;
		cin >> pos;
		Node *node = new Node;
		while (p && j < pos - 1) {
			p = p->next;
			j++;
		}
		if (!p || pos <= 0) {
			cout << "你要插入位置不符合!" << endl;
			return;
		}
		else {
			cout << "请输入学生姓名: ";
			cin >> node->name;
			cout << "请输入学生学号: ";
			cin >> node->num;
			cout << "请输入学生数学: ";
			cin >> node->math;
			cout << "请输入学生语文: ";
			cin >> node->chinese;
			cout << "请输入学生英语: ";
			cin >> node->English;
			node->ave = (node->math + node->chinese + node->English) / 3;
			//p->next指的是p节点指向下一个节点  node为新插入的节点
			node->next = p->next;//新插入的节点指向要插入的位置的结点指向下一个节点的地址
			p->next = node;//重新将要(插入位置的节点指向下一个节点的地址)指向新插入的节点的地址
		}
		cout << "插入成功!" << endl;
	}
}

void delete_stu(Student* &L) {
	if (!L) {
		cout << "该链表为空!" << endl;
		return;
	}
	Student *p = NULL, *q = NULL;
	p = L;
	int num = 0, index = 0;
	cout << "请输入你要删除学生的学号: ";
	cin >> num;
	while (p && p->next) {
		if (num == p->next->num) {	//要删除某学生要先找到该学生的前一个位置
			q = p->next;//然后在定义一个节点指向该学生地址
			p->next = q->next;//然后再将该学生前一个位置的下一个节点指向该学生下一个节点的位置
			q = NULL;
			delete q;
			cout << "删除成功!" << endl;
			index++;
		}
		p = p->next;
	}
	if (index == 0 ) cout << "未找到此学生!" << endl;
}

void menu() {

	Student *header = InitLink();
	

	char n;
	cout << "请输入你想实现的功能: ";
	while (1) {

		cin >> n;
		if (cin.fail()) {
			cin.clear();
			cin.sync();			//c++中表示清空缓冲区
			 //fflush(stdin);		//c语言中表示清空缓冲区
		}
		//int ret = cin.peek();		查看缓冲区内容
		//cout << ret << endl;
		//fflush(stdin);
		switch (n) {
		case '1':
			input_stu(header);		//输入学生信息
			break;
		case '2':
			insert_stu(header);		//插入学生信息
			break;
		case '3':
			rsearch_stu(header);		//查找学生信息
			break;
		case '4':
			print_stu(header);		//打印学生信息
			break;
		case '5':
			store_stu(header);		//保存学生信息
			break;
		case '6':
			delete_stu(header);			//删除学生信息
			break;
		case '7':
			statistick_stu(header);	//统计学生人数
			break;
		case '8':
			modify_stu(header);		//修改学生信息
			break;
		case '9':
			exit(1);
		default:
			cout << "输入错误，请重新输入: \n";
			break;
		}
		system("pause");
		system("cls");
		menuShow();
		cout << "请再次输入: ";
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
		cout << "初始化失败!" << endl;
		return NULL;
	}
	//header->count = 0;
	header->next = NULL;
	return header;
}

int main(void) {
	

	//初始化头结点
	InitLink();

	init();
	menuShow();
	menu();

	system("pause");
	return 0;
}