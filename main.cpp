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
	cout << "\n\n\n�д�α���� V1.0 .";
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
		//��¼�˵�
		cout << "\n��¼��\n\n 0���˳�\n 1������\n 2��ѧ��\n 3����ʦ\n";
		int ch = _getch();
		if (ch == '0')
			break;
		//����
		else if (ch == '1') {
			system("cls");
			cout << "\n����\n\n�û�����\n";
			string name;
			getline(cin, name);
			if (name.length() == 0) {
				cout << "��������";
				_getch();
				continue;
			}
			cout << "\n���룺\n";
			string password = Password();
			//ƥ��
			if (name != "admin" || password != "admin") {
				cout << "\n�û��������ڻ��������";
				_getch();
			}
			//����
			else {
				cout << "\n��¼�ɹ��� ...";
				Sleep(1000);
				while (1) {
					system("cls");
					//����˵�
					cout << "\n����\n\n 0������\n 1����������\n 2���γ̹���\n 3��ѧ������\n 4����ʦ����\n";
					int ch = _getch();
					if (ch == '0')
						break;
					else if (ch == '1') {
						system("cls");
						cout << "\n����> ��������\n\n";
						Instance->modifyNotice();
						_getch();
					}
					//�γ̹���
					else if (ch == '2') {
						while (1) {
							system("cls");
							//�γ̹���˵�
							cout << "\n����> �γ̹���\n\n 0������\n 1�����пγ�\n 2������\n 3���޸Ŀ���\n 4���޸Ŀ�����\n 5��ɾ���γ�\n";
							int ch = _getch();
							if (ch == '0')
								break;
							else if (ch == '1') {
								system("cls");
								cout << "\n����> �γ̹���> ���пγ�\n\n";
								Instance->diplayCourse();
								_getch();
							}
							else if (ch == '2') {
								system("cls");
								cout << "\n����> �γ̹���> ����\n\n";
								Instance->modifyCourse(0);
								_getch();
							}
							else if (ch == '3') {
								system("cls");
								cout << "\n����> �γ̹���> �޸Ŀ���\n\n";
								Instance->modifyCourse(1);
								_getch();
							}
							else if (ch == '4') {
								system("cls");
								cout << "\n����> �γ̹���> �޸Ŀ�����\n\n";
								Instance->modifyCourse(2);
								_getch();
							}
							else if (ch == '5') {
								system("cls");
								cout << "\n����> �γ̹���> ɾ���γ�\n\n";
								Instance->modifyCourse(3);
								_getch();
							}
						}
					}
					//ѧ������
					else if (ch == '3') {
						while (1) {
							system("cls");
							//ѧ������˵�
							cout << "\n����> ѧ������\n\n 0������\n 1�����ѧ��\n 2��ɾ��ѧ��\n 3������ѧ��\n 4���޸�����\n";
							int ch = _getch();
							if (ch == '0')
								break;
							else if (ch == '1') {
								system("cls");
								cout << "\n����> ѧ������> ���ѧ��\n\n";
								Instance->addUser(0);
								_getch();
							}
							else if (ch == '2') {
								system("cls");
								cout << "\n����> ѧ������> ɾ��ѧ��\n\n";
								Instance->handleUser(8, 0);
								_getch();
							}
							else if (ch == '3') {
								system("cls");
								cout << "\n����> ѧ������> ����ѧ��\n\n";
								Instance->studentCourse();
								_getch();
							}
							else if (ch == '4') {
								system("cls");
								cout << "\n����> ѧ������> �޸�����\n\n";
								Instance->handleUser(8, 1);
								_getch();
							}
						}
					}
					//��ʦ����
					else if (ch == '4') {
						while (1) {
							system("cls");
							//��ʦ����˵�
							cout << "\n����> ��ʦ����\n\n 0������\n 1����ӽ�ʦ\n 2��ɾ����ʦ\n 3�����ҽ�ʦ\n 4���޸�����\n";
							int ch = _getch();
							if (ch == '0')
								break;
							else if (ch == '1') {
								system("cls");
								cout << "\n����> ��ʦ����> ��ӽ�ʦ\n\n";
								Instance->addUser(1);
								_getch();
							}
							else if (ch == '2') {
								system("cls");
								cout << "\n����> ��ʦ����> ɾ����ʦ\n\n";
								Instance->handleUser(6, 0);
								_getch();
							}
							else if (ch == '3') {
								system("cls");
								cout << "\n����> ��ʦ����> ���ҽ�ʦ\n\n";
								Instance->teacherCourse();
								_getch();
							}
							else if (ch == '4') {
								system("cls");
								cout << "\n����> ��ʦ����> �޸�����\n\n";
								Instance->handleUser(6, 1);
								_getch();
							}
						}
					}
				}
			}
		}
		//ѧ��
		else if (ch == '2') {
			system("cls");
			//α����
			studentInterface student;
			//��¼
			cout << "\nѧ��\n\n";
			if (!student.login())
				_getch();
			//����
			else {
				cout << "��¼�ɹ��� ...";
				Sleep(1000);
				while (1) {
					system("cls");
					//����
					cout << "\nѧ��\n";
					student.noticeBoard();
					//ѧ���˵�
					cout << "\n\n 0������\n 1�����пγ�\n 2��ѡ��\n 3���˿�\n 4����ѡ�γ�\n 5���޸�����\n";
					int ch = _getch();
					if (ch == '0')
						break;
					else if (ch == '1') {
						system("cls");
						cout << "\nѧ��> ���пγ�\n\n";
						Instance->diplayCourse();
						_getch();
					}
					else if (ch == '2') {
						system("cls");
						cout << "\nѧ��> ѡ��\n\n";
						student.selectCourse();
						_getch();
					}
					else if (ch == '3') {
						system("cls");
						cout << "\nѧ��> �˿�\n\n";
						student.deleteCourse();
						_getch();
					}
					else if (ch == '4') {
						system("cls");
						cout << "\nѧ��> ��ѡ�γ�\n\n";
						student.displayCourse();
						_getch();
					}
					else if (ch == '5') {
						system("cls");
						cout << "\nѧ��> �޸�����\n\n";
						student.changePassword();
						_getch();
					}
				}
			}
		}
		//��ʦ
		else if (ch == '3') {
			system("cls");
			//α����
			teacherInterface teacher;
			//��¼
			cout << "\n��ʦ\n\n";
			if (!teacher.login())
				_getch();
			//����
			else {
				cout << "\n��¼�ɹ��� ...";
				Sleep(1000);
				while (1) {
					system("cls");
					//����
					cout << "\n��ʦ\n";
					teacher.noticeBoard();
					//��ʦ�˵�
					cout << "\n\n 0������\n 1��ȫУ�γ�\n 2�������γ�\n 3���ν̿γ�\n 4���޸�����\n";
					int ch = _getch();
					if (ch == '0')
						break;
					else if (ch == '1') {
						system("cls");
						cout << "\n��ʦ> ȫУ�γ�\n\n";
						Instance->diplayCourse();
						_getch();
					}
					else if (ch == '2') {
						system("cls");
						cout << "\n��ʦ> �����γ�\n\n";
						teacher.addCourse();
						_getch();
					}
					else if (ch == '3') {
						system("cls");
						cout << "\n��ʦ> �ν̿γ�\n\n";
						teacher.displayCourse();
						_getch();
					}
					else if (ch == '4') {
						system("cls");
						cout << "\n��ʦ> �޸�����\n\n";
						teacher.changePassword();
						_getch();
					}
				}
			}
		}	
	}
	system("cls");
	cout << "\n\n\n���ڱ��� .";
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
	cout << "\n\n\n����ɹ���";
	Sleep(500);
	return 0;
}