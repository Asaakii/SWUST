#include<iostream>

#include "WorkerManager.h"
#include "Company.h"

using namespace std;

int main()
{
	Company company;//��˾���Ӷ���
	company.show_company();//��ӡ��˾��Ϣ
	WorkerManager wm;//ʵ���������߶���
	int choice = 0;//�洢�û���ѡ��

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
		default:
			system("cls");//����
			break;
		}
	}

	system("pause");
	return 0;
}
