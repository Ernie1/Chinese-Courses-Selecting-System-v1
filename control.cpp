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
		cerr << "δ֪��������ϵ����Ա��";
		system("pause");
	}
}
//0ѧ����1��ʦ
void control::addUser(int p) {
	cout << "������\n";
	string name;
	getline(cin, name);
	if (name.length() == 0|| name.length() > 20) {
		cout << "��������";
		return;
	}
	if (p == 0) {
		student.push_back(user(name, studentAmount++));
		cout << "��ӳɹ�����ţ�" << studentAmount - 1;
	}
	else {
		teacher.push_back(user(name, teacherAmount++));
		cout << "��ӳɹ�����ţ�" << teacherAmount - 1;
	}
}
//8ѧ����6��ʦ��0ɾ����1�޸�����
void control::handleUser(int p, int q) {
	cout << "ѧ��/���ţ�\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != p) {
		cout << "��������";
		return;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "��������";
		return;
	}
	//ѧ��
	if (p == 8) {
		auto iter = find_if(student.begin(), student.end(), findUser(id));
		if (iter == student.end()) {
			cout << "�û�������";
			return;
		}
		//ɾ��
		if (q == 0) {
			//ɾ���γ̵�ѧ����Ϣ iter����ѧ�� itor��id itar������
			for (auto itor = iter->courseId.begin(); itor != iter->courseId.end(); ++itor) {
				auto itar = find_if(course.begin(), course.end(), findCourse(*itor));
				itar->studentId.erase(find(itar->studentId.begin(), itar->studentId.end(), id));
			}
			//ɾ��ѧ��
			student.erase(iter);
			cout << "�ɹ�ɾ����";
		}
		//�޸�
		else {
			cout << "�����룺\n";
			string password;
			getline(cin, password);
			if (password.length() == 0) {
				cout << "��������";
				return;
			}
			iter->password = password;
			cout << "���ĳɹ���";
		}
	}
	//��ʦ
	if (p == 6) {
		auto iter = find_if(teacher.begin(), teacher.end(), findUser(id));
		if (iter == teacher.end()) {
			cout << "�û�������";
			return;
		}
		//ɾ��
		if (q == 0) {
			//ɾ�����ѧ��
			//iter��ʦ itor�γ̺� itar�����γ� iturѧ����� itir����ѧ��
			for (auto itor = iter->courseId.begin(); itor != iter->courseId.end(); ++itor) {
				auto itar = find_if(course.begin(), course.end(), findCourse(*itor));
				for (auto itur = itar->studentId.begin(); itur != itar->studentId.end(); ++itur) {
					auto itir = find_if(student.begin(), student.end(), findUser(*itur));
					itir->courseId.erase(find(itir->courseId.begin(), itir->courseId.end(), *itor));
				}
				//ɾ���γ�
				stringstream tem;
				tem << "\n�γ̡�" << itar->name << "������ţ�" << itar->id << "���ѱ�ȡ��";
				notice += tem.str();
				//����
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
			//ɾ����ʦ
			teacher.erase(iter);
			cout << "ɾ���ɹ���";
		}
		//�޸�
		else {
			cout << "�����룺\n";
			string password;
			getline(cin, password);
			if (password.length() == 0) {
				cout << "��������";
				return;
			}
			iter->password = password;
			cout << "���ĳɹ���";
		}
	}
}
//��ʾ�γ�������ѡ����
void control::diplayCourse() {
	if (course.empty()) {
		cout << "���޿γ�";
		return;
	}
	cout << "���  �γ�                                     ��ʦ                 ����\n";
	//����
	for (auto iter = course.begin(); iter != course.end(); iter++)
		cout << iter->id << " " << left << setw(40) << iter->name << " " << left << setw(20) << iter->teacherName << " (" << iter->studentId.size() << "/" << iter->limit << ")\n";
}
//��ʾ���˿γ�
void control::studentCourse() {
	cout << "ѧ�ţ�\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != 8) {
		cout << "��������";
		return;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "��������";
		return;
	}
	auto iter = find_if(student.begin(), student.end(), findUser(id));
	if (iter == student.end()) {
		cout << "�û������ڣ�";
		return;
	}
	cout << "������\n" << iter->name << "\n\n";
	//��ʾ�γ�
	if (iter->courseId.empty()) {
		cout << "���޿γ�";
		return;
	}
	cout << "���  �γ�                                     ��ʦ                 ����\n";
	//����
	for (auto itir = iter->courseId.begin(); itir != iter->courseId.end(); ++itir) {
		auto itor = find_if(course.begin(), course.end(), findCourse(*itir));
		cout << itor->id << " " << left << setw(40) << itor->name << " " << left << setw(20) << itor->teacherName << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
void control::teacherCourse() {
	cout << "���ţ�\n";
	string idStr;
	getline(cin, idStr);
	if (idStr.length() != 6) {
		cout << "��������";
		return;
	}
	int id = stringToNum(idStr);
	if (id == -1) {
		cout << "��������";
		return;
	}
	auto iter = find_if(teacher.begin(), teacher.end(), findUser(id));
	if (iter == teacher.end()) {
		cout << "�û������ڣ�";
		return;
	}
	cout << "������\n" << iter->name << "\n\n";
	//��ʾ
	if (iter->courseId.empty()) {
		cout << "���޿γ�";
		return;
	}
	cout << "���  �γ�                                     ����\n";
	//����
	for (auto itir = iter->courseId.begin(); itir != iter->courseId.end(); ++itir) {
		auto itor = find_if(course.begin(), course.end(), findCourse(*itir));
		cout << itor->id << " " << left << setw(40) << itor->name << " (" << itor->studentId.size() << "/" << itor->limit << ")\n";
	}
}
//���в�����
void control::modifyNotice() {
	cout << "��ǰ��\n" << notice << "\n\n������\n";
	string n;
	getline(cin, n);
	if (n.length() == 0) {
		cout << "��������";
		return;
	}
	notice += '\n';
	notice += n;
	//����
	int p = -1, count = 0;
	while (1) {
		p = notice.find('\n', p + 1);
		if (p == -1)
			break;
		count++;
	}
	if (count == 6)
		notice = notice.substr(notice.find('\n', 1), notice.length() - notice.find('\n', 1));
	cout << "�����ɹ���";
}
//�޸� ��ʾ0 �γ���1 ����2 ɾ��3
void control::modifyCourse(int p) {
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
	auto iter = find_if(course.begin(), course.end(), findCourse(id));
	if (iter == course.end()) {
		cout << "�޴˿γ�";
		return;
	}
	//��ʾ
	if (p == 0) {
		cout << "���  �γ�                                     ��ʦ                 ����\n";
		cout << iter->id << " " << left << setw(40) << iter->name << " " << left << setw(20) << iter->teacherName << " (" << iter->studentId.size() << "/" << iter->limit << ")\n";
	}
	//�γ���
	else if (p == 1) {
		cout << "��ǰ��\n" << iter->name << "\n\n���£�\n";
		string name;
		getline(cin, name);
		if (name.length() == 0 || name.length() > 40) {
			cout << "��������";
			return;
		}
		iter->name = name;
		cout << "���ĳɹ���";
	}
	//����
	else if (p == 2) {
		cout << "��ǰ��\n" << iter->limit << "\n\n���£�\n";
		string num;
		getline(cin, num);
		int n = stringToNum(num);
		if (n == -1) {
			cout << "��������";
			return;
		}
		if (num.length() > 4) {
			cout << "�����������ƣ�";
			return;
		}
		iter->limit = n;
		cout << "���ĳɹ���";
	}
	//ɾ��
	else {
		//ɾ��ʦ�Ŀ� itor������ʦ
		auto itor = find_if(teacher.begin(), teacher.end(), findUser(iter->teacherId));
		itor->courseId.erase(find(itor->courseId.begin(), itor->courseId.end(), iter->id));
		//ɾѧ�� iturѧ����� itir����ѧ��
		for (auto itur = iter->studentId.begin(); itur != iter->studentId.end(); ++itur) {
			auto itir = find_if(student.begin(), student.end(), findUser(*itur));
			itir->courseId.erase(find(itir->courseId.begin(), itir->courseId.end(), iter->id));
		}
		//ɾ���γ�
		stringstream tem;
		tem << "\n�γ̡�" << iter->name << "������ţ�" << iter->id << "���ѱ�ȡ��";
		notice += tem.str();
		//����
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
		cout << "ɾ���ɹ���";
	}
}

control* control::instance = NULL;
control* control::getInstance() {
	if (instance == NULL)
		instance = new control;
	return instance;
}