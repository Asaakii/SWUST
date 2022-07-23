#pragma once
#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>

using namespace std;
//公司类
class Company
{
private:
	//公司名
	string ComName;
	//公司信息
	string ComRelevant;
	//公司总支出
	float ComExpend;
	//公司总收入
	float ComIncome;

public:
	//构造函数
	Company();

	//析构函数
	~Company();

	//打印公司信息
	void show_company();
};
#endif // !COMPANY_H