#pragma once
#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>

#include "Staff.h"

using namespace std;

//��˾��
class Company
{
private:
	string ComName;				//��˾��
	string ComRelevant;			//��˾��Ϣ
	float ComExpend;			//��˾��֧��
	float ComIncome;			//��˾����
public:
	int number;
	Company();					//�յĹ��캯��
	~Company();					//�������� 
	Staff* staf[10000];			//ָ�롢��������
	void show_company();		//��ʾ��˾��Ϣ����
	void search_staff();		//��ѯԱ����Ϣ����
	void add_staff();			//����Ա������
	void delete_staff();		//ɾ��Ա������
	void change_staff();		//�޸�Ա������
};
#endif // !COMPANY_H
