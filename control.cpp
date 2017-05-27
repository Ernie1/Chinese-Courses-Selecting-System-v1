#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<iomanip>
#include"control.h"
#include"global.h"
using namespace std;
int courseT::count = 10000;

control::control() {
	studentAmount = 10000000;
	teacherAmount = 100000;
	ifstream c("student.ini", ios::binary | ios::in);
	ifstream o("teacher.ini", ios::binary | ios::in);
	ifstream m("course.ini", ios::binary | ios::in);
	ifstream e("data.ini", ios::binary | ios::in);
	if (c.is_open() && o.is_open() && m.is_open() && e.is_open()) {
		while (c.peek() != EOF) {
			user tem;
			string line1, line4, line5;
			getline(c, line1);
			getline(c, tem.password);
			getline(c, tem.name);
			getline(c, line4);
			getline(c, line5);
			stringstream L1(line1), L4(line4), L5(line5);
			L1 >> tem.id;
			int size, num;
			L4 >> size;
			for (int i = 0; i < size; i++) {
				L5 >> num;
				tem.courseId.push_back(num);
			}
			student.push_back(tem);
		}
		c.close();
		while (o.peek() != EOF) {
			user tem;
			string line1, line4, line5;
			getline(o, line1);
			getline(o, tem.password);
			getline(o, tem.name);
			getline(o, line4);
			getline(o, line5);
			stringstream L1(line1), L4(line4), L5(line5);
			L1 >> tem.id;
			int size, num;
			L4 >> size;
			for (int i = 0; i < size; i++) {
				L5 >> num;
				tem.courseId.push_back(num);
			}
			teacher.push_back(tem);
		}
		o.close();
		while (m.peek() != EOF) {
			courseT tem;
			string line1, line3, line4, line6, line7;
			getline(m, line1);
			getline(m, tem.name);
			getline(m, line3);
			getline(m, line4);
			getline(m, tem.teacherName);
			getline(m, line6); 
			getline(m, line7);
			stringstream L1(line1), L3(line3), L4(line4), L6(line6), L7(line7);
			L1 >> tem.id;
			L3 >> tem.limit;
			L4 >> tem.teacherId;
			int size, num;
			L6 >> size;
			for (int i = 0; i < size; i++) {
				L7 >> num;
				tem.studentId.push_back(num);
			}
			course.push_back(tem);
		}
		m.close();
		e >> studentAmount >> teacherAmount >> courseT::count;
		string tem;
		getline(e, tem);
		getline(e, tem);
		while (e.peek() != EOF) {
			getline(e, tem);
			notice += '\n';
			notice += tem;
		}
		e.close();
	}
}
void control::save() {
	ofstream o("student.ini", ios::binary | ios::out);
	ofstream u("teacher.ini", ios::binary | ios::out);
	ofstream t("course.ini", ios::binary | ios::out);
	ofstream out("data.ini", ios::binary | ios::out);
	if (o.is_open() && u.is_open() && t.is_open() && out.is_open()) {
		for (auto &x : student) {
			o << x.id << endl << x.password << endl << x.name << endl << x.courseId.size() << endl;
			for (auto &y : x.courseId)
				o << y << " ";
			o << endl;
		}
		o.close();
		for (auto &x : teacher) {
			u << x.id << endl << x.password << endl << x.name << endl << x.courseId.size() << endl;
			for (auto &y : x.courseId)
				u << y << " ";
			u << endl;
		}
		u.close();
		for (auto &x : course) {
			t << x.id << endl << x.name << endl << x.limit << endl << x.teacherId << endl << x.teacherName << endl << x.studentId.size() << endl;
			for (auto &y : x.studentId)
				t << y << " ";
			t << endl;
		}
		t.close();
		out << studentAmount << endl << teacherAmount << endl << courseT::count << endl << notice << endl;
		out.close();
	}
	else {
		cerr << "未知错误，请联系技术员！";
		system("pause");
	}
}
//0学生，1老师
void control::addUser(int p) {
	cout << "姓名：\n";
	string name;
	getline(cin, name);
	if (name.length() == 0|| name.length() > 20) {
		cout << "输入有误！";
		return;
	}
	if (p == 0) {
		student.push_back(user(name, studentAmount++));
		cout << "添加成功！编号：" << studentAmount - 1;
	}
	else {
		teacher.push_back(user(name, teacherAmount++));
		cout << "添加成功！编号：" << teacherAmount - 1;
	}
}
//8学生，6老师，0删除，1修改密码
void control::handleUser(int p, int q) {
	cout << "学号/工号：\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != p) {
		cout << "输入有误！";
		return;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "输入有误！";
		return;
	}
	//学生
	if (p == 8) {
		auto iter = find_if(student.begin(), student.end(), findUser(id));
		if (iter == student.end()) {
			cout << "用户不存在";
			return;
		}
		//删除
		if (q == 0) {
			//删除课程的学生信息 iter完整学生 itor课id itar完整课
			for (auto itor = iter->courseId.begin(); itor != iter->courseId.end(); ++itor) {
				auto itar = find_if(course.begin(), course.end(), findCourse(*itor));
				itar->studentId.erase(find(itar->studentId.begin(), itar->studentId.end(), id));
			}
			//删除学生
			student.erase(iter);
			cout << "成功删除！";
		}
		//修改
		else {
			cout << "新密码：\n";
			string password;
			getline(cin, password);
			if (password.length() == 0) {
				cout << "输入有误！";
				return;
			}
			iter->password = password;
			cout << "更改成功！";
		}
	}
	//教师
	if (p == 6) {
		auto iter = find_if(teacher.begin(), teacher.end(), findUser(id));
		if (iter == teacher.end()) {
			cout << "用户不存在";
			return;
		}
		//删除
		if (q == 0) {
			//删除相关学生
			//iter老师 itor课程号 itar完整课程 itur学生编号 itir完整学生
			for (auto itor = iter->courseId.begin(); itor != iter->courseId.end(); ++itor) {
				auto itar = find_if(course.begin(), course.end(), findCourse(*itor));
				for (auto itur = itar->studentId.begin(); itur != itar->studentId.end(); ++itur) {
					auto itir = find_if(student.begin(), student.end(), findUser(*itur));
					itir->courseId.erase(find(itir->courseId.begin(), itir->courseId.end(), *itor));
				}
				//删除课程
				stringstream tem;
				tem << "\n课程“" << itar->name << "”（编号：" << itar->id << "）已被取消";
				notice += tem.str();
				//行数
				int p = -1, count = 0;
				while (1) {
					p = notice.find('\n', p + 1);
					if (p == -1)
						break;
					count++;
				}
				if (count == 6)
					notice = notice.substr(notice.find('\n', 1), notice.length() - notice.find('\n', 1));
				course.erase(itar);
			}
			//删除老师
			teacher.erase(iter);
			cout << "删除成功！";
		}
		//修改
		else {
			cout << "新密码：\n";
			string password;
			getline(cin, password);
			if (password.length() == 0) {
				cout << "输入有误！";
				return;
			}
			iter->password = password;
			cout << "更改成功！";
		}
	}
}
//显示课程名和已选人数
void control::diplayCourse() {
	if (course.empty()) {
		cout << "暂无课程";
		return;
	}
	cout << "编号  课程                                     教师                 人数\n";
	//遍历
	for (auto iter = course.begin(); iter != course.end(); iter++)
		cout << iter->id << " " << left << setw(40) << iter->name << " " << left << setw(20) << iter->teacherName << " (" << iter->studentId.size() << "/" << iter->limit << ")\n";
}
//显示个人课程
void control::studentCourse() {
	cout << "学号：\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != 8) {
		cout << "输入有误！";
		return;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "输入有误！";
		return;
	}
	auto iter = find_if(student.begin(), student.end(), findUser(id));
	if (iter == student.end()) {
		cout << "用户不存在！";
		return;
	}
	cout << "姓名：\n" << iter->name << "\n\n";
	//显示课程
	if (iter->courseId.empty()) {
		cout << "暂无课程";
		return;
	}
	cout << "编号  课程                                     教师                 人数\n";
	//遍历
	for (auto itir = iter->courseId.begin(); itir != iter->courseId.end(); ++itir) {
		auto itor = find_if(course.begin(), course.end(), findCourse(*itir));
		cout << itor->id << " " << left << setw(40) << itor->name << " " << left << setw(20) << itor->teacherName << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
void control::teacherCourse() {
	cout << "工号：\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != 6) {
		cout << "输入有误！";
		return;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "输入有误！";
		return;
	}
	auto iter = find_if(teacher.begin(), teacher.end(), findUser(id));
	if (iter == teacher.end()) {
		cout << "用户不存在！";
		return;
	}
	cout << "姓名：\n" << iter->name << "\n\n";
	//显示
	if (iter->courseId.empty()) {
		cout << "暂无课程";
		return;
	}
	cout << "编号  课程                                     人数\n";
	//遍历
	for (auto itir = iter->courseId.begin(); itir != iter->courseId.end(); ++itir) {
		auto itor = find_if(course.begin(), course.end(), findCourse(*itir));
		cout << itor->id << " " << left << setw(40) << itor->name << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
//单行布告栏
void control::modifyNotice() {
	cout << "当前：\n" << notice << "\n\n发布：\n";
	string n;
	getline(cin, n);
	if (n.length() == 0) {
		cout << "输入有误！";
		return;
	}
	notice += '\n';
	notice += n;
	//行数
	int p = -1, count = 0;
	while (1) {
		p = notice.find('\n', p + 1);
		if (p == -1)
			break;
		count++;
	}
	if (count == 6)
		notice = notice.substr(notice.find('\n', 1), notice.length() - notice.find('\n', 1));
	cout << "发布成功！";
}
//修改 显示0 课程名1 人数2 删除3
void control::modifyCourse(int p) {
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
	auto iter = find_if(course.begin(), course.end(), findCourse(id));
	if (iter == course.end()) {
		cout << "无此课程";
		return;
	}
	//显示
	if (p == 0) {
		cout << "编号  课程                                     教师                 人数\n";
		cout << iter->id << " " << left << setw(40) << iter->name << " " << left << setw(20) << iter->teacherName << " (" << iter->studentId.size() << "/" << iter->limit << ")\n";
	}
	//课程名
	else if (p == 1) {
		cout << "当前：\n" << iter->name << "\n\n更新：\n";
		string name;
		getline(cin, name);
		if (name.length() == 0 || name.length() > 40) {
			cout << "输入有误！";
			return;
		}
		iter->name = name;
		cout << "更改成功！";
	}
	//人数
	else if (p == 2) {
		cout << "当前：\n" << iter->limit << "\n\n更新：\n";
		string num;
		getline(cin, num);
		int n = stringToNum(num);
		if (n == -1) {
			cout << "输入有误！";
			return;
		}
		if (num.length() > 4) {
			cout << "超出人数限制！";
			return;
		}
		iter->limit = n;
		cout << "更改成功！";
	}
	//删除
	else {
		//删老师的课 itor完整老师
		auto itor = find_if(teacher.begin(), teacher.end(), findUser(iter->teacherId));
		itor->courseId.erase(find(itor->courseId.begin(), itor->courseId.end(), iter->id));
		//删学生 itur学生编号 itir完整学生
		for (auto itur = iter->studentId.begin(); itur != iter->studentId.end(); ++itur) {
			auto itir = find_if(student.begin(), student.end(), findUser(*itur));
			itir->courseId.erase(find(itir->courseId.begin(), itir->courseId.end(), iter->id));
		}
		//删除课程
		stringstream tem;
		tem << "\n课程“" << iter->name << "”（编号：" << iter->id << "）已被取消";
		notice += tem.str();
		//行数
		int p = -1, count = 0;
		while (1) {
			p = notice.find('\n', p + 1);
			if (p == -1)
				break;
			count++;
		}
		if (count == 6)
			notice = notice.substr(notice.find('\n', 1), notice.length() - notice.find('\n', 1));
		course.erase(iter);
		cout << "删除成功！";
	}
}

control* control::instance = NULL;
control* control::getInstance() {
	if (instance == NULL)
		instance = new control;
	return instance;
}