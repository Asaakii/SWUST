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
	cout << "��˾��֧����";
	cin >> ComExpend;
	cout << "��˾�����룺";
	cin >> ComIncome;
}

//��ʾ��˾��Ϣ
void Company::show_company()
{
	cout << "******************" << endl;
	cout << "��˾��Ϣ" << endl;
	cout << "��˾���֣�" << ComName << endl << "��˾�����Ϣ��" << ComRelevant << endl << "��˾��֧����" << ComExpend << endl << "��˾�����룺" << ComIncome << endl;
}

//��������
Company::~Company()
{

}