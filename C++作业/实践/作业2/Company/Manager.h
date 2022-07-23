#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include<iostream>

#include"Worker.h"

using namespace std;

//经理类
class Manager :public Worker
{
public:
	//构造函数
	Manager(int id, string name, string sex, int age, string idcard, float salary, int number);

	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();

	//析构函数
	~Manager();
};
#endif // !MANAGER_H