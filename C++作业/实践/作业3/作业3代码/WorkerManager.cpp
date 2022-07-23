#include"WorkerManager.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

//���캯��
WorkerManager::WorkerManager()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	//�ļ�����������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������!" << endl;//�������
		this->m_EmpNum = 0;//��ʼ������
		this->m_FilesEmpty = true;//��ʼ���ļ�Ϊ�ձ�־
		this->m_EmpArray = NULL;//��ʼ�������ָ��
		ifs.close();//�ر��ļ�
		return;
	}

	//2���ļ�������û������
	char ch;
	ifs >> ch;
	if (ifs.eof())//�ļ�Ϊ��
	{
		//cout << "�ļ�Ϊ��!" << endl;//�������
		this->m_EmpNum = 0;//��ʼ������
		this->m_FilesEmpty = true;//��ʼ���ļ�Ϊ�ձ�־
		this->m_EmpArray = NULL;//��ʼ�������ָ��
		ifs.close();//�ر��ļ�
		return;
	}

	//3���ļ������ұ�������
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;//���Դ���
	this->m_EmpNum = num;//���³�Ա����

	//4����ʼ�����
	//����ְ�����������飬���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//��ʼ��ְ�� ���ļ������ݣ��浽������
	this->init_Emp();
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
	cout << "************* 6�����ձ������ *************" << endl;
	cout << "************* 7����������ĵ� *************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

//�˳��������
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);//�������Ƕδ��룬���øú��������˳�
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
		//��������¿ռ��С
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

		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;//�ͷŵ������飬��[]

								  //�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//�ɹ���Ӻ� ���浽�ļ���
		this->save();

		//�ɹ���Ӻ� ����ְ����Ϊ�ձ�־
		this->m_FilesEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

	}
	else
	{
		cout << "���������������" << endl;
	}

	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�������ʽ���ļ�����д�ļ�
	//��ÿ��������д���ļ���
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

//ͳ������
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
		//��¼����
		num++;
	}
	ifs.close();
	return num;
}

//��ʼ��Ա��
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
		//���ݲ�ͬ�Ĳ���Id������ͬ�Ķ���
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
		//����������
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
	return;
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FilesEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}

//����ְ������ж�ְ���Ƿ����
//�����ڷ���ְ���������е�λ�ã������ڷ���-1
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

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FilesEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ְ����Ž���ɾ��
		int id = 0;
		cout << "����������ɾ����Ա����ţ�" << endl;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "ɾ��ʧ�ܣ����޴���" << endl;
		}
		else//˵��ְ�����ڣ�����Ҫɾ��indexλ���ϵ�ְ��
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼��Ա����

			//����ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ�!" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FilesEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ְ����Ž����޸�
		int id = 0;
		cout << "�����������޸ĵ�Ա����ţ�" << endl;
		cin >> id;

		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
		else//˵��ְ�����ڣ�����Ҫ�޸�indexλ���ϵ�ְ��
		{
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

			this->save();
			cout << "�޸ĳɹ�!" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FilesEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
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
			else//˵��ְ�����ڣ�����Ҫ����indexλ���ϵ�ְ��
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

			bool flag = false;//���ҵ��ı�־
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

	}
	//�����������
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Sort_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FilesEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ����Ž�������" << endl;
		cout << "2����ְ����Ž��н���" << endl;
		int select = 0;
		cin >> select;

		//ѡ������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;//������Сֵ �� ���ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrMax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
				else//����
				{
					if (this->m_EmpArray[minOrMax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
			}
			//�ж�һ��ʼ�϶��� ���ֵ������Сֵ �ǲ��� ��������ֵ����Сֵ
			//������ǽ�������
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();//�����ı��浽�ļ���
		this->Show_Emp();//��ʾְ������
	}
}

//��պ���
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete m_EmpArray[i];
				}
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FilesEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	//�������������
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