#pragma once
#ifndef STAFF_H
#define STAFF_H

#include<iostream>
#include<string>

using namespace std;

//Ա���� 
class Staff
{
private:
	string name;				//Ա������
	int age;					//Ա������
	string sex;					//Ա���Ա�
	string id;					//Ա�����֤��
	string worknumber;			//Ա������
	float salary;				//Ա������
public:
	Staff();					//�յĹ��캯��
	float get_salary();			//��ù���
	string get_name();			//�������
	string get_worknumber();	//��ù���
	string get_id();			//������֤��
	string get_sex();			//����Ա�
	int get_age();				//�������
	void show_staff();			//������ʾԱ����Ϣ����
};
#endif // !STAFF_H
