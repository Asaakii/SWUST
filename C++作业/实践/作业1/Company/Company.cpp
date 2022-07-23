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
	cout << "公司员工工资支出：";
	cin >> ComExpend;
	cout << "公司收入：";
	cin >> ComIncome;
	cout << "公司员工个数：";
	cin >> number;
}

//显示公司信息
void Company::show_company()
{
	cout << "******************" << endl;
	cout << "公司信息" << endl;
	cout << "公司名字：" << ComName << endl << "公司相关信息：" << ComRelevant << endl << "公司员工工资总支出：" << ComExpend << endl << "公司收入：" << ComIncome << endl << "公司员工个数：" << number << endl;
	cout << "员工信息" << endl;
}

//查询员工信息
void Company::search_staff()
{
	string n;						//定义员工姓名n
	int i, count = 0;
	cout << "请输入员工姓名：";
	cin >> n;						//输入姓名
	for (i = 0; i < number; i++)
	{
		if (staf[i] != NULL)		//空指针判断输入是否有效
		{
			if (staf[i]->get_name() == n)			//判断是否已存在输入名
			{
				staf[i]->show_staff();				//提取显示信息函数
				count++;
			}
		}
		else
		{											//如果输入无效
			cout << "没有查询到此员工！" << endl;
		}
	}
	if (count == 0)									//如果输入不存在
		cout << "没有查询到此员工！" << endl;
}

//增加员工
void Company::add_staff()
{
	int n, i;
	cout << "请输入增加员工的数量：";
	cin >> n;
	for (i = number; i < number + n; i++)
	{
		staf[i] = new Staff;						//在堆空间产生对象
	}
	number += n;									//增加后的员工数
	cout << endl << "恭喜你成功地增加了" << n << "个成员" << endl;
}

//删除员工
void Company::delete_staff()
{
	string n;
	cout << "请输入要删除员工姓名：";
	cin >> n;
	for (int i = 0; i < number; i++)
	{
		if (staf[i]->get_name() == n)				//判断输入是否存在
		{
			staf[i] = NULL;							//空指针
			cout << "删除成功！" << endl;
			cout << endl;
		}
	}
}

//修改员工数据
void Company::change_staff()
{
	string n;
	cout << "请输入要修改员工姓名：";
	cin >> n;
	for (int i = 0; i < number; i++)
	{
		if (staf[i]->get_name() == n)
		{
			staf[i] = NULL;							//删除
			staf[i] = new Staff;					//在堆空间产生对象
			cout << "修改成功！" << endl;
			cout << endl;
		}
		else
			cout << "修改失败，没有此员工！" << endl;
	}
}

//析构函数
Company::~Company()
{

}