#include"WorkerManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

//构造函数
WorkerManager::WorkerManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	//文件不存在现象
	if (!ifs.is_open())
	{
		//cout << "文件不存在!" << endl;//测试输出
		this->m_EmpNum = 0;//初始化人数
		this->m_FilesEmpty = true;//初始化文件为空标志
		this->m_EmpArray = NULL;//初始化数组的指针
		ifs.close();//关闭文件
		return;
	}

	//2、文件存在且没有数据
	char ch;
	ifs >> ch;
	if (ifs.eof())//文件为空
	{
		//cout << "文件为空!" << endl;//测试输出
		this->m_EmpNum = 0;//初始化人数
		this->m_FilesEmpty = true;//初始化文件为空标志
		this->m_EmpArray = NULL;//初始化数组的指针
		ifs.close();//关闭文件
		return;
	}

	//3、文件存在且保存数据
	int num = this->get_EmpNum();
	//cout << "职工个数为：" << num << endl;//测试代码
	this->m_EmpNum = num;//更新成员属性

	//4、初始化完成
	//根据职工数创建数组，开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//初始化职工 将文件中数据，存到数组中
	this->init_Emp();
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
	cout << "************* 6、按照编号排序 *************" << endl;
	cout << "************* 7、清空所有文档 *************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

//退出管理程序
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);//无论在那段代码，调用该函数都会退出
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
		//计算添加新空间大小
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

		//释放原有的空间
		delete[] this->m_EmpArray;//释放的是数组，加[]

								  //更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//成功添加后 保存到文件中
		this->save();

		//成功添加后 更新职工不为空标志
		this->m_FilesEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

	}
	else
	{
		cout << "您输入的数据有误！" << endl;
	}

	//按任意键后 清屏回到上级目录
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出方式打开文件——写文件
	//将每个人数据写到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_sex << " "
			<< this->m_EmpArray[i]->m_age << " "
			<< this->m_EmpArray[i]->m_idcard << " "
			<< this->m_EmpArray[i]->m_salary << " "
			<< this->m_EmpArray[i]->m_number << " " << endl;
	}
	ofs.close();
}

//统计人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	string sex;
	int age;
	string idcard;
	float salary;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> sex && ifs >> age && ifs >> idcard && ifs >> salary && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	string sex;
	int age;
	string idcard;
	float salary;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> sex && ifs >> age && ifs >> idcard && ifs >> salary && ifs >> dId)
	{
		Worker* worker = NULL;
		//根据不同的部门Id创建不同的对象
		if (dId == 1)
		{
			worker = new Employee(id, name, sex, age, idcard, salary, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, sex, age, idcard, salary, dId);
		}
		else
		{
			worker = new Boss(id, name, sex, age, idcard, salary, dId);
		}
		//存在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
	return;
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FilesEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//按照职工编号判断职工是否存在
//若存在返回职工在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
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
	if (this->m_FilesEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		//按照职工编号进行删除
		int id = 0;
		cout << "请输入您想删除的员工编号：" << endl;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "删除失败，查无此人" << endl;
		}
		else//说明职工存在，并且要删除index位置上的职工
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数

			//数据同步更新到文件中
			this->save();
			cout << "删除成功!" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FilesEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		//按照职工编号进行修改
		int id = 0;
		cout << "请输入您想修改的员工编号：" << endl;
		cin >> id;

		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "修改失败，查无此人" << endl;
		}
		else//说明职工存在，并且要修改index位置上的职工
		{
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

			this->save();
			cout << "修改成功!" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FilesEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
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
			else//说明职工存在，并且要查找index位置上的职工
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

			bool flag = false;//查找到的标志
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

	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//排序职工
void WorkerManager::Sort_Emp()
{
	//判断文件是否为空
	if (this->m_FilesEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工编号进行升序" << endl;
		cout << "2、按职工编号进行降序" << endl;
		int select = 0;
		cin >> select;

		//选择排序
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值 或 最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
				else//降序
				{
					if (this->m_EmpArray[minOrMax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定的 最大值或者最小值 是不是 计算的最大值或最小值
			//如果不是交换数据
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->save();//排序后的保存到文件中
		this->Show_Emp();//显示职工函数
	}
}

//清空函数
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete m_EmpArray[i];
				}
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FilesEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	//按任意键后清屏
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