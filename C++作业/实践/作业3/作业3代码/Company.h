#pragma once
#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>

using namespace std;
//��˾��
class Company
{
private:
	//��˾��
	string ComName;
	//��˾��Ϣ
	string ComRelevant;
	//��˾��֧��
	float ComExpend;
	//��˾������
	float ComIncome;

public:
	//���캯��
	Company();

	//��������
	~Company();

	//��ӡ��˾��Ϣ
	void show_company();
};
#endif // !COMPANY_H