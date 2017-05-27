#include"interface.h"
#include"global.h"
#include<iomanip>
using namespace std;

control* globalInstance = control::getInstance();

//��¼
bool Interface::login() {
	cout << "ѧ��/���ţ�\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != role) {
		cout << "��������";
		return false;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "��������";
		return false;
	}
	//ѧ��
	list<user>* container = &(globalInstance->student);
	//��ʦ
	if (role == 6)
		container = &(globalInstance->teacher);
	//id������
	auto iter = find_if(container->begin(), container->end(), findUser(id));
	if (iter == container->end()) {
		cout << "�û�������";
		return false;
	}
	cout << "\n���룺\n";
	string password = Password();
	if (password != iter->password) {
		cout << "�������";
		return false;
	}
	me = &(*iter);
	cout << "\n" << iter->name << "����ӭ������\n";
	return true;
}
//����
void Interface::noticeBoard() {
	if (globalInstance->notice.length() == 0)
		cout << "����֪ͨ";
	else
		cout << globalInstance->notice;
}
//������
void Interface::changePassword() {
	cout << "�����룺\n";
	string password;
	getline(cin, password);
	if (password.length() == 0) {
		cout << "��������";
		return;
	}
	me->password = password;
	cout << "���ĳɹ���";
}

studentInterface::studentInterface() { role = 8; }
//ѡ�� 
void studentInterface::selectCourse() {
	cout << "�γ̱�ţ�\n";
	string num;
	getline(cin, num);
	if (num.length() != 5) {
		cout << "��������";
		return;
	}
	int id = stringToNum(num);
	if (id == -1) {
		cout << "��������";
		return;
	}
	//iter�Լ��Ŀα�
	auto iter = find(me->courseId.begin(), me->courseId.end(), id);
	if (iter != me->courseId.end()) {
		cout << "��ѡ�ÿ�";
		return;
	}
	//itor�����Ŀ�
	auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(id));
	if (itor == globalInstance->course.end()) {
		cout << "�޴˿γ�";
		return;
	}
	if (itor->studentId.size() == itor->limit) {
		cout << "��������";
		return;
	}
	me->courseId.push_back(id);
	itor->studentId.push_back(me->id);
	cout << "ѡ�γɹ���";
}
//��ʾ��
void studentInterface::displayCourse() {
	if (me->courseId.empty()) {
		cout << "���޿γ�";
		return;
	}
	cout << "���  �γ�                                     ��ʦ                 ����\n";
	//iter��id itor������
	for (auto iter = me->courseId.begin(); iter != me->courseId.end(); ++iter) {
		auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(*iter));
		cout << itor->id << " " << left << setw(40) << itor->name << " " << left << setw(20) << itor->teacherName << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
//��ѡ
void studentInterface::deleteCourse() {
	cout << "�γ̱�ţ�\n";
	string num;
	getline(cin, num);
	if (num.length() != 5) {
		cout << "��������";
		return;
	}
	int id = stringToNum(num);
	if (id == -1) {
		cout << "��������";
		return;
	}
	//iter��id itor������
	auto iter = find(me->courseId.begin(), me->courseId.end(), id);
	if (iter == me->courseId.end()) {
		cout << "δѡ�ÿ�";
		return;
	}
	me->courseId.erase(iter);
	auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(id));
	itor->studentId.erase(find(itor->studentId.begin(), itor->studentId.end(), me->id));
	cout << "��ѡ�ɹ���";
}

	
teacherInterface::teacherInterface() { role = 6; }
//��ʾ��
void teacherInterface::displayCourse() {
	if (me->courseId.empty()) {
		cout << "���޿γ�";
		return;
	}
	cout << "���  �γ�                                     ����\n";
	//iter��id itor������
	for (auto iter = me->courseId.begin(); iter != me->courseId.end(); iter++) {
		auto itor = find_if(globalInstance->course.begin(), globalInstance->course.end(), findCourse(*iter));
		cout << itor->id << " " << left << setw(40) << itor->name << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
//Ψһ�Ŀγ���ӹ���
void teacherInterface::addCourse() {
	cout << "�γ����ƣ�\n";
	string name;
	getline(cin, name);
	if (name.length() == 0|| name.length() > 40) {
		cout << "��������";
		return;
	}
	cout << "��������\n";
	string num;
	getline(cin, num);
	int n = stringToNum(num);
	if (n == -1 || n == 0) {
		cout << "��������";
		return;
	}
	if (num.length() > 4) {
		cout << "�����������ƣ�";
		return;
	}
	globalInstance->course.push_back(courseT(name, n, me->id, me->name));
	cout << "��ӳɹ�����ţ�" << courseT::count - 1;
	me->courseId.push_back(courseT::count - 1);
	stringstream tem;
	tem << "\n" << me->name << "��ʦ�����ˡ�" << name << "���γ̣���ţ�" << courseT::count - 1;
	globalInstance->notice += tem.str();
	//����
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