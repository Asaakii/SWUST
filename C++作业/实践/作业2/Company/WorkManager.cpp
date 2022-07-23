#include"WorkerManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

//���캯��
WorkerManager::WorkerManager()
{
	//��ʼ������
	this->m_EmpNum = 0;
	//��ʼ�������ָ��
	this->m_EmpArray = NULL;
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "*******************************************" << endl;
	cout << "********** ��ӭʹ��ְ������ϵͳ��**********" << endl;
	cout << "************* 0���˳�������� *************" << endl;
	cout << "************* 1������ְ����Ϣ *************" << endl;
	cout << "************* 2����ʾְ����Ϣ *************" << endl;
	cout << "************* 3��ɾ����ְְ�� *************" << endl;
	cout << "************* 4���޸�ְ����Ϣ *************" << endl;
	cout << "************* 5������ְ����Ϣ *************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

//�˳��������
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//����ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְ��������" << endl;
	int addNum = 0;//�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		int newSize = this->m_EmpNum + addNum;//�¿ռ�����=ԭ����¼����+��������

		//�����¿ռ䣬�����Ƕ�̬��ӵ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���Ŀռ������ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			string sex;
			int age;
			string idcard;
			float salary;
			int dSelest;//ְ�����ڲ������Ʊ��

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ�����֣�" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "����ְ���Ա�" << endl;
			cin >> sex;
			cout << "�������" << i + 1 << "����ְ�����䣺" << endl;
			cin >> age;
			cout << "�������" << i + 1 << "����ְ�����֤�ţ�" << endl;
			cin >> idcard;
			cout << "�������" << i + 1 << "����ְ�����ʣ�" << endl;
			cin >> salary;
			cout << "�������" << i + 1 << "����ְ����λ��" << endl;
			cout << "����1��ʾ��ͨԱ��������2��ʾ��˾��������3��ʾ��˾�ϰ�" << endl;
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
			//��������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;

		cout << "�ɹ����" << addNum << "����ְ��" << endl;

	}
	else
	{
		cout << "���������������" << endl;
	}

	system("pause");
	system("cls");
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	for (int i = 0; i < m_EmpNum; i++)
	{
		//���ö�̬���ó���ӿ�
		this->m_EmpArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	//����ְ����Ž���ɾ��
	int id = 0;
	cout << "����������ɾ����Ա����ţ�" << endl;
	cin >> id;
	int index = this->IsExist(id);
	for (int i = index; i < this->m_EmpNum - 1; i++)
	{
		this->m_EmpArray[i] = this->m_EmpArray[i + 1];
	}
	this->m_EmpNum--;

	cout << "ɾ���ɹ�!" << endl;

	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	//����ְ����Ž����޸�
	int id = 0;
	cout << "�����������޸ĵ�Ա����ţ�" << endl;
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

	cout << "�鵽:" << id << "��ְ������������ְ���ţ�" << endl;
	cin >> newid;

	cout << "�������µ�������" << endl;
	cin >> newname;

	cout << "�������µ��Ա�" << endl;
	cin >> newsex;

	cout << "�������µ����䣺" << endl;
	cin >> newage;

	cout << "�������µ����֤�ţ�" << endl;
	cin >> newidcard;

	cout << "�������µĹ��ʣ�" << endl;
	cin >> newsalary;

	cout << "�������µ�ְλ��" << endl;
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
	//�������ݵ�������
	this->m_EmpArray[index] = work;

	cout << "�޸ĳɹ�!" << endl;

	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	cout << "��������ҵķ�ʽ��" << endl;
	cout << "1����ְ����Ų���" << endl;
	cout << "2����ְ����������" << endl;
	int select = 0;
	cin >> select;

	//����ְ����Ž��в���
	if (select == 1)
	{
		int id = 0;
		cout << "������������ҵ�Ա����ţ�" << endl;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "����ʧ�ܣ����޴���" << endl;
		}
		else
		{
			cout << "���ҳɹ���ְ����Ϣ���£�" << endl;
			this->m_EmpArray[index]->showInfo();
		}
	}
	else if (select == 2)//��ְ����������
	{
		string name;
		cout << "������������ҵ�Ա��������" << endl;
		cin >> name;

		bool flag = false;//���ҵ�
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (name == this->m_EmpArray[i]->m_name)
			{
				cout << "���ҳɹ���ְ�����Ϊ"
					<< this->m_EmpArray[i]->m_id
					<< "�ŵ���Ϣ���£�" << endl;
				flag = true;
				this->m_EmpArray[i]->showInfo();
			}
		}
		if (flag == false)
		{
			cout << "����ʧ�ܣ����޴���" << endl;
		}
	}
	else
	{
		cout << "����������" << endl;
	}
	system("pause");
	system("cls");
}

//��������
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}