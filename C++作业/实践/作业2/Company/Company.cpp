#include <iostream>
#include <string>

#include "Company.h"

using namespace std;

Company::Company()
{
	cout << "请输入公司的相关信息" << endl;
	cout << "公司名：";
	cin >> ComName;
	cout << "公司信息：";
	cin >> ComRelevant;
	cout << "公司总支出：";
	cin >> ComExpend;
	cout << "公司总收入：";
	cin >> ComIncome;
}

//显示公司信息
void Company::show_company()
{
	cout << "******************" << endl;
	cout << "公司信息" << endl;
	cout << "公司名字：" << ComName << endl << "公司相关信息：" << ComRelevant << endl << "公司总支出：" << ComExpend << endl << "公司总收入：" << ComIncome << endl;
}

//析构函数
Company::~Company()
{

}