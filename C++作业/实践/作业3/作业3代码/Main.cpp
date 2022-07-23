#include<iostream>

#include"WorkerManager.h"
#include "Company.h"
#include "Information.h"

using namespace std;

int main()
{
	Information inf[100];//用户信息的数组
	int a = 0;//用户的个数
	int c, e;//功能选择
	char* u;//登录时用户名输入
	char* p;//登录时密码输入
	int a1, b1;//控制判断条件
	for (int d = 0; d < 100; d++) {
		cout << "1-注册；2-登录:";//功能选择
		cin >> c;
		switch (c)
		{
		case 1:
		{
			for (int i = 0; i <= 100; i++)
			{
				int con = inf[i].setinformation();//用户注册
				a1 = 0;
				for (int j = 0; j < a; j++)
				{
					char* f = inf[j].getUsers();
					char* h = inf[a].getUsers();
					if (strlen(f) == strlen(h))
					{
						int judge2 = 0;
						int o;
						for (o = 0; o < strlen(f); o++)
						{
							if (*(f + o) == *(h + o))   judge2 = judge2 + 1;
						}
						if (judge2 == o)
						{
							cout << "用户名已存在，请重新设置" << endl; i--;
							a1 = 1;
							inf[a].deleteusers();
							a--;
							break;
						}
					}
				}
				if (con == 0 && a1 == 0)
				{
					cout << "两次输入密码不相同，请重新设置" << endl;
					i--;
					inf[a].deleteusers();
					a--;
				}
				else if (con == 1 && a1 == 0)  cout << "设置成功！" << endl;
				a = a + 1;//个数加一
				cout << "'1'继续，'2'返回" << endl;//是否继续注册
				cin >> e;
				if (e == 2) { break; }
				else if (e == 1)
				{
					continue;
				}
				else if (e != 1 && e != 2)
				{
					cout << "输入无效" << endl;
					break;
				}
			}
			break;
		}
		case 2: {
			cout << "请输入用户名： ";
			u = (char*)malloc(20 * sizeof(char));
			cin >> u;
			cout << "请输入密码：  ";
			p = (char*)malloc(20 * sizeof(char));
			cin >> p;
			for (int z = 0; z <= a; z++)
			{
				b1 = inf[z].Login(u, p);
				if (b1 == 0)
				{
					cout << "登录成功！" << endl << "欢迎使用此系统！" << endl;
					Company company;//公司类子对象
					company.show_company();//打印公司信息
					WorkerManager wm;//实例化管理者对象
					int choice = 0;//用来存储用户的选项

					while (true)
					{
						//调用展示菜单成员函数
						wm.Show_Menu();
						cout << "请输入您的选择：" << endl;
						cin >> choice;//接收用户的选项

						switch (choice)
						{
						case 0://退出管理程序
							wm.ExitSystem();
							break;
						case 1://增加职工信息
							wm.Add_Emp();
							break;
						case 2://显示职工信息
							wm.Show_Emp();
							break;
						case 3://删除离职职工
							wm.Del_Emp();
							break;
						case 4://修改职工信息
							wm.Mod_Emp();
							break;
						case 5://查找职工信息
							wm.Find_Emp();
							break;
						case 6://按照编号排序
							wm.Sort_Emp();
							break;
						case 7://清空所有文档
							wm.Clean_File();
							break;
						default:
							break;
						}
					}
					break;
				}//登录成功
			}
			if (b1 == 1) cout << "The user is not exist or the password is wrong." << endl;//登录失败
			break;
		}
		default: cout << "abnormal input" << endl;
		}
	}

	

	return 0;
}