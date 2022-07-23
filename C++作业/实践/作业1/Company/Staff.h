#pragma once
#ifndef STAFF_H
#define STAFF_H

#include<iostream>
#include<string>

using namespace std;

//员工类 
class Staff
{
private:
	string name;				//员工姓名
	int age;					//员工年龄
	string sex;					//员工性别
	string id;					//员工身份证号
	string worknumber;			//员工工号
	float salary;				//员工工资
public:
	Staff();					//空的构造函数
	float get_salary();			//获得工资
	string get_name();			//获得姓名
	string get_worknumber();	//获得工号
	string get_id();			//获得身份证号
	string get_sex();			//获得性别
	int get_age();				//获得年龄
	void show_staff();			//声明显示员工信息函数
};
#endif // !STAFF_H
