#include"WorkerManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

//构造函数
WorkerManager::WorkerManager()
{
	//初始化人数
	this->m_EmpNum = 0;
	//初始化数组的指针
	this->m_EmpArray = NULL;
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "*******************************************" << endl;
	cout << "********** 欢迎使用职工管理系统！**********" << endl;
	cout << "************* 0、退出管理程序 *************" << endl;
	cout << "************* 1、增加职工信息 *************" << endl;
	cout << "************* 2、显示职工信息 *************" << endl;
	cout << "************* 3、删除离职职工 *************" << endl;
	cout << "************* 4、修改职工信息 *************" << endl;
	cout << "************* 5、查找职工信息 *************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

//退出管理程序
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//增加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量：" << endl;
	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		int newSize = this->m_EmpNum + addNum;//新空间人数=原来记录人数+新增人数

		//开辟新空间，数组是动态添加的
		Worker** newSpace = new Worker * [newSize];

		//将原来的空间下数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			string sex;
			int age;
			string idcard;
			float salary;
			int dSelest;//职工所在部门名称编号

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工名字：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新职工性别：" << endl;
			cin >> sex;
			cout << "请输入第" << i + 1 << "个新职工年龄：" << endl;
			cin >> age;
			cout << "请输入第" << i + 1 << "个新职工身份证号：" << endl;
			cin >> idcard;
			cout << "请输入第" << i + 1 << "个新职工工资：" << endl;
			cin >> salary;
			cout << "请输入第" << i + 1 << "个新职工岗位：" << endl;
			cout << "输入1表示普通员工，输入2表示公司经理，输入3表示公司老板" << endl;
			cin >> dSelest;

			Worker* worker = NULL;
			switch (dSelest)
			{
			case 1:
				worker = new Employee(id, name, sex, age, idcard, salary, 1);
				break;
			case 2:
				worker = new Manager(id, name, sex, age, idcard, salary, 2);
				break;
			case 3:
				worker = new Boss(id, name, sex, age, idcard, salary, 3);
				break;
			default:
				break;
			}
			//将创建的职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;

		cout << "成功添加" << addNum << "名新职工" << endl;

	}
	else
	{
		cout << "您输入的数据有误！" << endl;
	}

	system("pause");
	system("cls");
}

//显示职工
void WorkerManager::Show_Emp()
{
	for (int i = 0; i < m_EmpNum; i++)
	{
		//利用多态调用程序接口
		this->m_EmpArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (id == this->m_EmpArray[i]->m_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	//按照职工编号进行删除
	int id = 0;
	cout << "请输入您想删除的员工编号：" << endl;
	cin >> id;
	int index = this->IsExist(id);
	for (int i = index; i < this->m_EmpNum - 1; i++)
	{
		this->m_EmpArray[i] = this->m_EmpArray[i + 1];
	}
	this->m_EmpNum--;

	cout << "删除成功!" << endl;

	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	//按照职工编号进行修改
	int id = 0;
	cout << "请输入您想修改的员工编号：" << endl;
	cin >> id;

	int index = this->IsExist(id);
	delete this->m_EmpArray[index];

	int newid = 0;
	string newname = "";
	string newsex = "";
	int newage = 0;
	string newidcard = "";
	float newsalary = 0;
	int dselect = 0;

	cout << "查到:" << id << "号职工，请输入新职工号：" << endl;
	cin >> newid;

	cout << "请输入新的姓名：" << endl;
	cin >> newname;

	cout << "请输入新的性别：" << endl;
	cin >> newsex;

	cout << "请输入新的年龄：" << endl;
	cin >> newage;

	cout << "请输入新的身份证号：" << endl;
	cin >> newidcard;

	cout << "请输入新的工资：" << endl;
	cin >> newsalary;

	cout << "请输入新的职位：" << endl;
	cin >> dselect;

	Worker* work = NULL;
	switch (dselect)
	{
	case 1:
		work = new Employee(newid, newname, newsex, newage, newidcard, newsalary, dselect);
		break;
	case 2:
		work = new Manager(newid, newname, newsex, newage, newidcard, newsalary, dselect);
		break;
	case 3:
		work = new Boss(newid, newname, newsex, newage, newidcard, newsalary, dselect);
		break;
	default:
		break;
	}
	//更新数据到数组中
	this->m_EmpArray[index] = work;

	cout << "修改成功!" << endl;

	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	cout << "请输入查找的方式：" << endl;
	cout << "1、按职工编号查找" << endl;
	cout << "2、按职工姓名查找" << endl;
	int select = 0;
	cin >> select;

	//按照职工编号进行查找
	if (select == 1)
	{
		int id = 0;
		cout << "请输入您想查找的员工编号：" << endl;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "查找失败，查无此人" << endl;
		}
		else
		{
			cout << "查找成功！职工信息如下：" << endl;
			this->m_EmpArray[index]->showInfo();
		}
	}
	else if (select == 2)//按职工姓名查找
	{
		string name;
		cout << "请输入您想查找的员工姓名：" << endl;
		cin >> name;

		bool flag = false;//查找到
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (name == this->m_EmpArray[i]->m_name)
			{
				cout << "查找成功，职工编号为"
					<< this->m_EmpArray[i]->m_id
					<< "号的信息如下：" << endl;
				flag = true;
				this->m_EmpArray[i]->showInfo();
			}
		}
		if (flag == false)
		{
			cout << "查找失败，查无此人" << endl;
		}
	}
	else
	{
		cout << "输入项有误" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}