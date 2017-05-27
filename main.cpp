#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<string>
#include<sstream>
#include"control.h"
#include"global.h"
#include"interface.h"

using namespace std;

int main() {
	cout << "\n\n\n中大伪教务 V1.0 .";
	control* Instance = control::getInstance();
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	while (1) {
		system("cls");
		//登录菜单
		cout << "\n登录：\n\n 0、退出\n 1、教务\n 2、学生\n 3、教师\n";
		int ch = _getch();
		if (ch == '0')
			break;
		//教务
		else if (ch == '1') {
			system("cls");
			cout << "\n教务\n\n用户名：\n";
			string name;
			getline(cin, name);
			if (name.length() == 0) {
				cout << "输入有误！";
				_getch();
				continue;
			}
			cout << "\n密码：\n";
			string password = Password();
			//匹配
			if (name != "admin" || password != "admin") {
				cout << "\n用户名不存在或密码错误";
				_getch();
			}
			//进入
			else {
				cout << "\n登录成功！ ...";
				Sleep(1000);
				while (1) {
					system("cls");
					//教务菜单
					cout << "\n教务\n\n 0、返回\n 1、发布公告\n 2、课程管理\n 3、学生管理\n 4、教师管理\n";
					int ch = _getch();
					if (ch == '0')
						break;
					else if (ch == '1') {
						system("cls");
						cout << "\n教务> 发布公告\n\n";
						Instance->modifyNotice();
						_getch();
					}
					//课程管理
					else if (ch == '2') {
						while (1) {
							system("cls");
							//课程管理菜单
							cout << "\n教务> 课程管理\n\n 0、返回\n 1、所有课程\n 2、查找\n 3、修改课名\n 4、修改课容量\n 5、删除课程\n";
							int ch = _getch();
							if (ch == '0')
								break;
							else if (ch == '1') {
								system("cls");
								cout << "\n教务> 课程管理> 所有课程\n\n";
								Instance->diplayCourse();
								_getch();
							}
							else if (ch == '2') {
								system("cls");
								cout << "\n教务> 课程管理> 查找\n\n";
								Instance->modifyCourse(0);
								_getch();
							}
							else if (ch == '3') {
								system("cls");
								cout << "\n教务> 课程管理> 修改课名\n\n";
								Instance->modifyCourse(1);
								_getch();
							}
							else if (ch == '4') {
								system("cls");
								cout << "\n教务> 课程管理> 修改课容量\n\n";
								Instance->modifyCourse(2);
								_getch();
							}
							else if (ch == '5') {
								system("cls");
								cout << "\n教务> 课程管理> 删除课程\n\n";
								Instance->modifyCourse(3);
								_getch();
							}
						}
					}
					//学生管理
					else if (ch == '3') {
						while (1) {
							system("cls");
							//学生管理菜单
							cout << "\n教务> 学生管理\n\n 0、返回\n 1、添加学生\n 2、删除学生\n 3、查找学生\n 4、修改密码\n";
							int ch = _getch();
							if (ch == '0')
								break;
							else if (ch == '1') {
								system("cls");
								cout << "\n教务> 学生管理> 添加学生\n\n";
								Instance->addUser(0);
								_getch();
							}
							else if (ch == '2') {
								system("cls");
								cout << "\n教务> 学生管理> 删除学生\n\n";
								Instance->handleUser(8, 0);
								_getch();
							}
							else if (ch == '3') {
								system("cls");
								cout << "\n教务> 学生管理> 查找学生\n\n";
								Instance->studentCourse();
								_getch();
							}
							else if (ch == '4') {
								system("cls");
								cout << "\n教务> 学生管理> 修改密码\n\n";
								Instance->handleUser(8, 1);
								_getch();
							}
						}
					}
					//教师管理
					else if (ch == '4') {
						while (1) {
							system("cls");
							//教师管理菜单
							cout << "\n教务> 教师管理\n\n 0、返回\n 1、添加教师\n 2、删除教师\n 3、查找教师\n 4、修改密码\n";
							int ch = _getch();
							if (ch == '0')
								break;
							else if (ch == '1') {
								system("cls");
								cout << "\n教务> 教师管理> 添加教师\n\n";
								Instance->addUser(1);
								_getch();
							}
							else if (ch == '2') {
								system("cls");
								cout << "\n教务> 教师管理> 删除教师\n\n";
								Instance->handleUser(6, 0);
								_getch();
							}
							else if (ch == '3') {
								system("cls");
								cout << "\n教务> 教师管理> 查找教师\n\n";
								Instance->teacherCourse();
								_getch();
							}
							else if (ch == '4') {
								system("cls");
								cout << "\n教务> 教师管理> 修改密码\n\n";
								Instance->handleUser(6, 1);
								_getch();
							}
						}
					}
				}
			}
		}
		//学生
		else if (ch == '2') {
			system("cls");
			//伪单例
			studentInterface student;
			//登录
			cout << "\n学生\n\n";
			if (!student.login())
				_getch();
			//进入
			else {
				cout << "登录成功！ ...";
				Sleep(1000);
				while (1) {
					system("cls");
					//公告
					cout << "\n学生\n";
					student.noticeBoard();
					//学生菜单
					cout << "\n\n 0、返回\n 1、所有课程\n 2、选课\n 3、退课\n 4、已选课程\n 5、修改密码\n";
					int ch = _getch();
					if (ch == '0')
						break;
					else if (ch == '1') {
						system("cls");
						cout << "\n学生> 所有课程\n\n";
						Instance->diplayCourse();
						_getch();
					}
					else if (ch == '2') {
						system("cls");
						cout << "\n学生> 选课\n\n";
						student.selectCourse();
						_getch();
					}
					else if (ch == '3') {
						system("cls");
						cout << "\n学生> 退课\n\n";
						student.deleteCourse();
						_getch();
					}
					else if (ch == '4') {
						system("cls");
						cout << "\n学生> 已选课程\n\n";
						student.displayCourse();
						_getch();
					}
					else if (ch == '5') {
						system("cls");
						cout << "\n学生> 修改密码\n\n";
						student.changePassword();
						_getch();
					}
				}
			}
		}
		//教师
		else if (ch == '3') {
			system("cls");
			//伪单例
			teacherInterface teacher;
			//登录
			cout << "\n教师\n\n";
			if (!teacher.login())
				_getch();
			//进入
			else {
				cout << "\n登录成功！ ...";
				Sleep(1000);
				while (1) {
					system("cls");
					//公告
					cout << "\n教师\n";
					teacher.noticeBoard();
					//教师菜单
					cout << "\n\n 0、返回\n 1、全校课程\n 2、发布课程\n 3、任教课程\n 4、修改密码\n";
					int ch = _getch();
					if (ch == '0')
						break;
					else if (ch == '1') {
						system("cls");
						cout << "\n教师> 全校课程\n\n";
						Instance->diplayCourse();
						_getch();
					}
					else if (ch == '2') {
						system("cls");
						cout << "\n教师> 发布课程\n\n";
						teacher.addCourse();
						_getch();
					}
					else if (ch == '3') {
						system("cls");
						cout << "\n教师> 任教课程\n\n";
						teacher.displayCourse();
						_getch();
					}
					else if (ch == '4') {
						system("cls");
						cout << "\n教师> 修改密码\n\n";
						teacher.changePassword();
						_getch();
					}
				}
			}
		}	
	}
	system("cls");
	cout << "\n\n\n正在保存 .";
	Instance->save();
	delete Instance;
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	system("cls");
	cout << "\n\n\n保存成功！";
	Sleep(500);
	return 0;
}