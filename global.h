#ifndef GLOBAL_H
#define GLOBAL_H

#include<conio.h>
#include<string>
#include<sstream>
using namespace std;

//´íÎó·µ»Ø-1
inline int stringToNum(string source) {
	if (source.length() == 0)
		return -1;
	for (size_t i = 0; i < source.length(); i++)
		if (source[i]<'0' || source[i]>'9')
			return -1;
	stringstream s(source);
	int num;
	s >> num;
	return num;
}

inline string Password() {
	char password[100] = "\0";
	int index = 0;
	while (1) {
		char ch;
		ch = _getch();
		if (ch == 8) {
			if (index != 0) {
				std::cout << char(8) << " " << char(8);
				index--;
			}
		}
		else if (ch == '\r') {
			password[index] = '\0';
			cout << endl;
			if (password[0] != 0)
				break;
		}
		else {
			std::cout << "*";
			password[index++] = ch;
		}
	}
	string tem(password);
	return tem;
}

#endif