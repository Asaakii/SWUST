#pragma once
#ifndef WORKER_H
#define WORKER_H

#include<iostream>
#include<string>

using namespace std;

//ְ���������
class Worker
{
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	//ְ�����
	int m_id;
	//ְ������
	string m_name;
	//ְ���Ա�
	string m_sex;
	//ְ������
	int m_age;
	//ְ�����֤��
	string m_idcard;
	//ְ������
	float m_salary;
	//���ű��
	int m_number;
};
#endif // !WORKER_H