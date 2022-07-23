#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include<iostream>

#include "Worker.h"

using namespace std;

//普通员工类
class Employee :public Worker
{
public:
	//构造函数
	Employee(int id, string name, string sex, int age, string idcard, float salary, int number);

	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();

	//析构函数
	~Employee();
};
#endif // !EMPLOYEE_H