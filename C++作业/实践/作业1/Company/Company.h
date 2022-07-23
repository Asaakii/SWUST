#pragma once
#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>

#include "Staff.h"

using namespace std;

//公司类
class Company
{
private:
	string ComName;				//公司名
	string ComRelevant;			//公司信息
	float ComExpend;			//公司总支出
	float ComIncome;			//公司收入
public:
	int number;
	Company();					//空的构造函数
	~Company();					//析构函数 
	Staff* staf[10000];			//指针、对象数组
	void show_company();		//显示公司信息函数
	void search_staff();		//查询员工信息函数
	void add_staff();			//增加员工函数
	void delete_staff();		//删除员工函数
	void change_staff();		//修改员工函数
};
#endif // !COMPANY_H
