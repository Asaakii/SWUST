#include <iostream>
#include <string>

#include "Company.h"

using namespace std;

Company::Company()
{
	cout << "�����빫˾�������Ϣ" << endl;
	cout << "��˾����";
	cin >> ComName;
	cout << "��˾��Ϣ��";
	cin >> ComRelevant;
	cout << "��˾Ա������֧����";
	cin >> ComExpend;
	cout << "��˾���룺";
	cin >> ComIncome;
	cout << "��˾Ա��������";
	cin >> number;
}

//��ʾ��˾��Ϣ
void Company::show_company()
{
	cout << "******************" << endl;
	cout << "��˾��Ϣ" << endl;
	cout << "��˾���֣�" << ComName << endl << "��˾�����Ϣ��" << ComRelevant << endl << "��˾Ա��������֧����" << ComExpend << endl << "��˾���룺" << ComIncome << endl << "��˾Ա��������" << number << endl;
	cout << "Ա����Ϣ" << endl;
}

//��ѯԱ����Ϣ
void Company::search_staff()
{
	string n;						//����Ա������n
	int i, count = 0;
	cout << "������Ա��������";
	cin >> n;						//��������
	for (i = 0; i < number; i++)
	{
		if (staf[i] != NULL)		//��ָ���ж������Ƿ���Ч
		{
			if (staf[i]->get_name() == n)			//�ж��Ƿ��Ѵ���������
			{
				staf[i]->show_staff();				//��ȡ��ʾ��Ϣ����
				count++;
			}
		}
		else
		{											//���������Ч
			cout << "û�в�ѯ����Ա����" << endl;
		}
	}
	if (count == 0)									//������벻����
		cout << "û�в�ѯ����Ա����" << endl;
}

//����Ա��
void Company::add_staff()
{
	int n, i;
	cout << "����������Ա����������";
	cin >> n;
	for (i = number; i < number + n; i++)
	{
		staf[i] = new Staff;						//�ڶѿռ��������
	}
	number += n;									//���Ӻ��Ա����
	cout << endl << "��ϲ��ɹ���������" << n << "����Ա" << endl;
}

//ɾ��Ա��
void Company::delete_staff()
{
	string n;
	cout << "������Ҫɾ��Ա��������";
	cin >> n;
	for (int i = 0; i < number; i++)
	{
		if (staf[i]->get_name() == n)				//�ж������Ƿ����
		{
			staf[i] = NULL;							//��ָ��
			cout << "ɾ���ɹ���" << endl;
			cout << endl;
		}
	}
}

//�޸�Ա������
void Company::change_staff()
{
	string n;
	cout << "������Ҫ�޸�Ա��������";
	cin >> n;
	for (int i = 0; i < number; i++)
	{
		if (staf[i]->get_name() == n)
		{
			staf[i] = NULL;							//ɾ��
			staf[i] = new Staff;					//�ڶѿռ��������
			cout << "�޸ĳɹ���" << endl;
			cout << endl;
		}
		else
			cout << "�޸�ʧ�ܣ�û�д�Ա����" << endl;
	}
}

//��������
Company::~Company()
{

}