#include<iostream>

#include"WorkerManager.h"
#include "Company.h"
#include "Information.h"

using namespace std;

int main()
{
	Information inf[100];//�û���Ϣ������
	int a = 0;//�û��ĸ���
	int c, e;//����ѡ��
	char* u;//��¼ʱ�û�������
	char* p;//��¼ʱ��������
	int a1, b1;//�����ж�����
	for (int d = 0; d < 100; d++) {
		cout << "1-ע�᣻2-��¼:";//����ѡ��
		cin >> c;
		switch (c)
		{
		case 1:
		{
			for (int i = 0; i <= 100; i++)
			{
				int con = inf[i].setinformation();//�û�ע��
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
							cout << "�û����Ѵ��ڣ�����������" << endl; i--;
							a1 = 1;
							inf[a].deleteusers();
							a--;
							break;
						}
					}
				}
				if (con == 0 && a1 == 0)
				{
					cout << "�����������벻��ͬ������������" << endl;
					i--;
					inf[a].deleteusers();
					a--;
				}
				else if (con == 1 && a1 == 0)  cout << "���óɹ���" << endl;
				a = a + 1;//������һ
				cout << "'1'������'2'����" << endl;//�Ƿ����ע��
				cin >> e;
				if (e == 2) { break; }
				else if (e == 1)
				{
					continue;
				}
				else if (e != 1 && e != 2)
				{
					cout << "������Ч" << endl;
					break;
				}
			}
			break;
		}
		case 2: {
			cout << "�������û����� ";
			u = (char*)malloc(20 * sizeof(char));
			cin >> u;
			cout << "���������룺  ";
			p = (char*)malloc(20 * sizeof(char));
			cin >> p;
			for (int z = 0; z <= a; z++)
			{
				b1 = inf[z].Login(u, p);
				if (b1 == 0)
				{
					cout << "��¼�ɹ���" << endl << "��ӭʹ�ô�ϵͳ��" << endl;
					Company company;//��˾���Ӷ���
					company.show_company();//��ӡ��˾��Ϣ
					WorkerManager wm;//ʵ���������߶���
					int choice = 0;//�����洢�û���ѡ��

					while (true)
					{
						//����չʾ�˵���Ա����
						wm.Show_Menu();
						cout << "����������ѡ��" << endl;
						cin >> choice;//�����û���ѡ��

						switch (choice)
						{
						case 0://�˳��������
							wm.ExitSystem();
							break;
						case 1://����ְ����Ϣ
							wm.Add_Emp();
							break;
						case 2://��ʾְ����Ϣ
							wm.Show_Emp();
							break;
						case 3://ɾ����ְְ��
							wm.Del_Emp();
							break;
						case 4://�޸�ְ����Ϣ
							wm.Mod_Emp();
							break;
						case 5://����ְ����Ϣ
							wm.Find_Emp();
							break;
						case 6://���ձ������
							wm.Sort_Emp();
							break;
						case 7://��������ĵ�
							wm.Clean_File();
							break;
						default:
							break;
						}
					}
					break;
				}//��¼�ɹ�
			}
			if (b1 == 1) cout << "The user is not exist or the password is wrong." << endl;//��¼ʧ��
			break;
		}
		default: cout << "abnormal input" << endl;
		}
	}

	

	return 0;
}