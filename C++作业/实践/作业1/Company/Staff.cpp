#include<iostream>
#include<string>

#include "Staff.h"

using namespace std;

//����Ա����Ϣ
Staff::Staff()//����
{
    cout << "������Ա����Ϣ" << endl;

    cout << "Ա������: " << endl;
    cin >> name;

    cout << "Ա������: " << endl;
    cin >> age;

    cout << "Ա���Ա�:" << endl;
    cin >> sex;

    cout << "Ա�����֤��: " << endl;
    cin >> id;

    cout << "Ա������: " << endl;
    cin >> worknumber;

    cout << "Ա������: " << endl;
    cin >> salary;
}

void Staff::show_staff()//����ѽ�����Ա����Ϣ
{
    cout << "����: " << name << endl << "����: " << age << endl << "�Ա�:" << sex << endl << "���֤��: " << id << endl << "����: " << worknumber << endl << "����: " << salary << '\b' << endl;
}

float Staff::get_salary()       //��ȡÿ��Ա���Ĺ���
{
    return salary;
}

string Staff::get_name()        //��ȡÿ��Ա��������
{
    return name;
}

int Staff::get_age()            //��ȡÿ��Ա��������
{
    return age;
}

string Staff::get_sex()         //��ȡÿ��Ա�����Ա�
{
    return sex;
}

string Staff::get_id()          //��ȡÿ��Ա�������֤��
{
    return id;
}

string Staff::get_worknumber()  //��ȡÿ��Ա���Ĺ���
{
    return worknumber;
}