#include"interface.h"
#include"global.h"
#include<iomanip>
using namespace std;

control* globalInstance = control::getInstance();

//登录
bool Interface::login() {
	cout << "学号/工号：\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != role) {
		cout << "输入有误！";
		return false;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "输入有误！";
		return false;
	}
	//学生
	list<user>* container = &(globalInstance->student);
	//老师
	if (role == 6)
		container = &(globalInstance->teacher);
	//id找完整
	auto iter = find_if(container->begin(), container->end(), findUser(id));
	if (iter == container->end()) {
		cout << "用户不存在";
		return false;
	}
	cout << "\n密码：\n";
	string password = Password();
	if (password != iter->password) {
		cout << "密码错误";
		return false;
	}
	me = &(*iter);
	cout << "\n" << iter->name << "，欢迎回来！\n";
	return true;
}
//公告
void Interface::noticeBoard() {
	if (globalInstance->notice.length() == 0)
		cout << "暂无通知";
	else
		cout << globalInstance->notice;
}
//改密码
void Interface::changePassword() {
	cout << "新密码：\n";
	string password;
	getline(cin, password);
	if (password.length() == 0) {
		cout << "输入有误！";
		return;
	}
	me->password = password;
	cout << "更改成功！";
}

studentInterface::studentInterface() { role = 8; }
//选课 
void studentInterface::selectCourse() {
	cout << "课程编号：\n";
	string num;
	getline(cin, num);
	if (num.length() != 5) {
		cout << "输入有误！";
		return;
	}
	int id = stringToNum(num);
	if (id == -1) {
		cout << "输入有误！";
		return;
	}
	//iter自己的课表
	auto iter = find(me->courseId.begin(), me->courseId.end(), id);
	if (iter != me->courseId.end()) {
		cout << "已选该课";
		return;
	}
	//itor完整的课
	auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(id));
	if (itor == globalInstance->course.end()) {
		cout << "无此课程";
		return;
	}
	if (itor->studentId.size() == itor->limit) {
		cout << "人数已满";
		return;
	}
	me->courseId.push_back(id);
	itor->studentId.push_back(me->id);
	cout << "选课成功！";
}
//显示课
void studentInterface::displayCourse() {
	if (me->courseId.empty()) {
		cout << "暂无课程";
		return;
	}
	cout << "编号  课程                                     教师                 人数\n";
	//iter课id itor完整课
	for (auto iter = me->courseId.begin(); iter != me->courseId.end(); ++iter) {
		auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(*iter));
		cout << itor->id << " " << left << setw(40) << itor->name << " " << left << setw(20) << itor->teacherName << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
//退选
void studentInterface::deleteCourse() {
	cout << "课程编号：\n";
	string num;
	getline(cin, num);
	if (num.length() != 5) {
		cout << "输入有误！";
		return;
	}
	int id = stringToNum(num);
	if (id == -1) {
		cout << "输入有误！";
		return;
	}
	//iter课id itor完整课
	auto iter = find(me->courseId.begin(), me->courseId.end(), id);
	if (iter == me->courseId.end()) {
		cout << "未选该课";
		return;
	}
	me->courseId.erase(iter);
	auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(id));
	itor->studentId.erase(find(itor->studentId.begin(), itor->studentId.end(), me->id));
	cout << "退选成功！";
}

	
teacherInterface::teacherInterface() { role = 6; }
//显示课
void teacherInterface::displayCourse() {
	if (me->courseId.empty()) {
		cout << "暂无课程";
		return;
	}
	cout << "编号  课程                                     人数\n";
	//iter课id itor完整课
	for (auto iter = me->courseId.begin(); iter != me->courseId.end(); iter++) {
		auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(*iter));
		cout << itor->id << " " << left << setw(40) << itor->name << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
//唯一的课程添加功能
void teacherInterface::addCourse() {
	cout << "课程名称：\n";
	string name;
	getline(cin, name);
	if (name.length() == 0|| name.length() > 40) {
		cout << "输入有误！";
		return;
	}
	cout << "课容量：\n";
	string num;
	getline(cin, num);
	int n = stringToNum(num);
	if (n == -1 || n == 0) {
		cout << "输入有误！";
		return;
	}
	if (num.length() > 4) {
		cout << "超出人数限制！";
		return;
	}
	globalInstance->course.push_back(courseT(name, n, me->id, me->name));
	cout << "添加成功！编号：" << courseT::count - 1;
	me->courseId.push_back(courseT::count - 1);
	stringstream tem;
	tem << "\n" << me->name << "老师发布了“" << name << "”课程，编号：" << courseT::count - 1;
	globalInstance->notice += tem.str();
	//行数
	int p = -1, count = 0;
	while (1) {
		p = globalInstance->notice.find('\n', p + 1);
		if (p == -1)
			break;
		count++;
	}
	if (count == 6)
		globalInstance->notice = globalInstance->notice.substr(globalInstance->notice.find('\n', 1), globalInstance->notice.length() - globalInstance->notice.find('\n', 1));
}