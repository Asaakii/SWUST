#include <iostream>
#include <string>

#include "Staff.h"
#include "Company.h"

using namespace std;

int main()
{
	Company company;//公司类子对象
	cout << endl;
	for (int i = 0; i < company.number; i++)
	{
		company.staf[i] = new Staff;//新建员工
	}
	company.show_company();//打印公司信息
	for (int i = 0; i < company.number; i++)
	{
		company.staf[i]->show_staff();//打印员工信息
	}
	cout << endl;
	cout << "******************" << endl;
	while (1)
	{
		cout << "---------------------" << endl;
		cout << "1.查询员工信息" << endl;
		cout << "2.增加新员工" << endl;
		cout << "3.删除员工信息" << endl;
		cout << "4.修改员工信息" << endl;
		cout << "0.退出系统" << endl;
		cout << "---------------------" << endl;
		cout << "请输入你想选择的功能：" << endl;
		int num;
		cin >> num;//按钮
		cout << "--------------------" << endl;
		if (num == 0)//退出
			break;
		switch (num)
		{
		case 1:
			company.search_staff();//查询
			break;
		case 2:
			company.add_staff();//增加
			break;
		case 3:
			company.delete_staff();//删除
			break;
		case 4:
			company.change_staff();//修改
			break;
		default://输入错误
			cout << "请输入正确的操作指令" << endl;
			cout << "**************************" << endl;
		}
	}
	return 0;
}