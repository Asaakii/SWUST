#pragma once
#ifndef BOSS_H
#define BOSS_H

#include<iostream>

#include "Worker.h"

using namespace std;

//�ϰ���
class Boss :public Worker
{
public:
	//���캯��
	Boss(int id, string name, string sex, int age, string idcard, float salary, int number);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��λ����
	virtual string getDeptName();

	//��������
	~Boss();
};
#endif // !BOSS_H