#ifndef INTERFACE_H
#define INTERFACE_H
#include"control.h"
class Interface {
public:
	Interface(){}
	//登录
	bool login();
	//公告
	void noticeBoard();
	//改密码
	void changePassword();
protected:
	int role;
	user* me;
};

class studentInterface :public Interface {
public:
	studentInterface();
	//选课 
	void selectCourse();
	//显示课
	void displayCourse();
	//退选
	void deleteCourse();
};

class teacherInterface :public Interface {
public:
	teacherInterface();
	//显示课
	void displayCourse();
	//唯一的课程添加功能
	void addCourse();
};

#endif