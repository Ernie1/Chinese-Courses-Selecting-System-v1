#ifndef INTERFACE_H
#define INTERFACE_H
#include"control.h"
class Interface {
public:
	Interface(){}
	//��¼
	bool login();
	//����
	void noticeBoard();
	//������
	void changePassword();
protected:
	int role;
	user* me;
};

class studentInterface :public Interface {
public:
	studentInterface();
	//ѡ�� 
	void selectCourse();
	//��ʾ��
	void displayCourse();
	//��ѡ
	void deleteCourse();
};

class teacherInterface :public Interface {
public:
	teacherInterface();
	//��ʾ��
	void displayCourse();
	//Ψһ�Ŀγ���ӹ���
	void addCourse();
};

#endif