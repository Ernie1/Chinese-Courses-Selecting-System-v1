#ifndef CONTROL_H
#define CONTROL_H

#include<iostream>
#include<string>
#include<list>
#include<sstream>
#include<algorithm>
#include<conio.h>

using namespace std;

struct user {
	user(){}
	user(string Name, int Id) {
		id = Id;
		password = "0000";
		name = Name;
	}
	int id;
	string password;
	string name;
	list<int> courseId;
};

struct courseT {
	courseT(){}
	courseT(string Name, int Limit, int TeacherId, string TeacherName) {
		id = count++;
		name = Name;
		limit = Limit;
		teacherId = TeacherId;
		teacherName = TeacherName;
	}
	int id;
	string name;
	int teacherId;
	int limit;
	string teacherName;
	static int count;
	list<int> studentId;
};

//�ҿγ�
class findCourse {
public:
	findCourse(int id) :id(id) {}
	bool operator()(const courseT &p) {
		return id == p.id;
	}
private:
	int id;
};

//���û�
class findUser {
public:
	findUser(int id) :id(id) {}
	bool operator()(const user &p) {
		return id == p.id;
	}
private:
	int id;
};

class control {
public:
	//0ѧ����1��ʦ
	void addUser(int p);
	//8ѧ����6��ʦ��0ɾ����1�޸�����
	void handleUser(int p, int q);
	//��ʾ�γ�������ѡ����
	void diplayCourse();
	//��ʾ���˿γ�
	void studentCourse();
	void teacherCourse();
	//���в�����
	void modifyNotice();
	//�޸� ��ʾ0 �γ���1 ����2 ɾ��3
	void modifyCourse(int p);
	void save();
	//����
	static control* getInstance();
	list<user> student;
	list<user> teacher;
	list<courseT> course;
	string notice;
private:
	int studentAmount;
	int teacherAmount;
	control();
	static control* instance;
};

#endif