#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include<iostream>

#include "Worker.h"

using namespace std;

//��ͨԱ����
class Employee :public Worker
{
public:
	//���캯��
	Employee(int id, string name, string sex, int age, string idcard, float salary, int number);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��λ����
	virtual string getDeptName();

	//��������
	~Employee();
};
#endif // !EMPLOYEE_H