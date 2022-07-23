#pragma once
#ifndef WORKER_H
#define WORKER_H

#include<iostream>
#include<string>

using namespace std;

//职工抽象基类
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	//职工编号
	int m_id;
	//职工姓名
	string m_name;
	//职工性别
	string m_sex;
	//职工年龄
	int m_age;
	//职工身份证号
	string m_idcard;
	//职工工资
	float m_salary;
	//部门编号
	int m_number;
};
#endif // !WORKER_H