#pragma once
#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include<iostream>

#include"Worker.h"

using namespace std;

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//��������
	~WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳��������
	void ExitSystem();

	//��¼��������
	int m_EmpNum;

	//Ա�������ָ��
	Worker** m_EmpArray;

	//����ְ��
	void Add_Emp();

	//��ʾְ��
	void Show_Emp();

	//����ְ������ж�ְ���Ƿ����
	int IsExist(int id);

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();
};
#endif // !WORKERMANAGER_H