#pragma once
#ifndef INFORMATION_H
#define INFORMATION_H

#include <iostream>
using namespace std;

class Information
{
private:
	char* Users;//用户名
	char* Password;//密码
	char* Password1;//第二次输入的密码
	char* users;//登录时输入的用户名
	char* password;//登录时输入的密码
public:
	Information()
	{ //构造函数
		this->Users = Users, this->Password = Password;
	}

	~Information() {} //析构函数

	void deleteusers() {//用户名重复时删除该注册
		
	}

	int Login(char* users, char* password) {//登录
		int b = 1;//控制登录的成功或失败
		for (int o = 0, p = 0; o < strlen(Users) && o < strlen(users) && p < strlen(Password) && p < strlen(password); o++, p++) {
			if ((*(Users + o) == *(users + o)) && (*(Password + p) == *(password + p)))   b = 0;//成功为零，失败为一
			else { b = 1; break; }
		}
		return b;
	}

	int setinformation() {//注册
		int judge1 = 0;
		cout << "请设置您的用户名：";
		Users = (char*)malloc(20 * sizeof(char));
		cin >> Users;
		cout << "请设置您的密码：";
		Password = (char*)malloc(20 * sizeof(char));
		cin >> Password;
		cout << "请再次输入您设置的密码：";
		Password1 = (char*)malloc(20 * sizeof(char));
		cin >> Password1;//用户名密码输入
		if (strlen(Password) == strlen(Password1))
		{
			int p;
			for (p = 0; p < strlen(Password); p++)
			{
				if (*(Password + p) == *(Password1 + p))  judge1 = judge1 + 1; //判断两次输入的密码是否相等
			}
			if (judge1 == p) return 1;
			else return 0;
		}
		else return 0;
	}

	char* getUsers() { return Users; }//返回用户名以判断注册的用户名是否重复
};
#endif // !INFORMATION_H
