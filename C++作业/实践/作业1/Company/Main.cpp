#include <iostream>
#include <string>

#include "Staff.h"
#include "Company.h"

using namespace std;

int main()
{
	Company company;//��˾���Ӷ���
	cout << endl;
	for (int i = 0; i < company.number; i++)
	{
		company.staf[i] = new Staff;//�½�Ա��
	}
	company.show_company();//��ӡ��˾��Ϣ
	for (int i = 0; i < company.number; i++)
	{
		company.staf[i]->show_staff();//��ӡԱ����Ϣ
	}
	cout << endl;
	cout << "******************" << endl;
	while (1)
	{
		cout << "---------------------" << endl;
		cout << "1.��ѯԱ����Ϣ" << endl;
		cout << "2.������Ա��" << endl;
		cout << "3.ɾ��Ա����Ϣ" << endl;
		cout << "4.�޸�Ա����Ϣ" << endl;
		cout << "0.�˳�ϵͳ" << endl;
		cout << "---------------------" << endl;
		cout << "����������ѡ��Ĺ��ܣ�" << endl;
		int num;
		cin >> num;//��ť
		cout << "--------------------" << endl;
		if (num == 0)//�˳�
			break;
		switch (num)
		{
		case 1:
			company.search_staff();//��ѯ
			break;
		case 2:
			company.add_staff();//����
			break;
		case 3:
			company.delete_staff();//ɾ��
			break;
		case 4:
			company.change_staff();//�޸�
			break;
		default://�������
			cout << "��������ȷ�Ĳ���ָ��" << endl;
			cout << "**************************" << endl;
		}
	}
	return 0;
}