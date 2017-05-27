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

//找课程
class findCourse {
public:
	findCourse(int id) :id(id) {}
	bool operator()(const courseT &p) {
		return id == p.id;
	}
private:
	int id;
};

//找用户
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
	//0学生，1老师
	void addUser(int p);
	//8学生，6老师，0删除，1修改密码
	void handleUser(int p, int q);
	//显示课程名和已选人数
	void diplayCourse();
	//显示个人课程
	void studentCourse();
	void teacherCourse();
	//单行布告栏
	void modifyNotice();
	//修改 显示0 课程名1 人数2 删除3
	void modifyCourse(int p);
	void save();
	//单例
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