#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include<iostream>

#include"Worker.h"

using namespace std;

//������
class Manager :public Worker
{
public:
	//���캯��
	Manager(int id, string name, string sex, int age, string idcard, float salary, int number);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��λ����
	virtual string getDeptName();

	//��������
	~Manager();
};
#endif // !MANAGER_H