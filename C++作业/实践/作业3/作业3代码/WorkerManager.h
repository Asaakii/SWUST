#pragma once
#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include<iostream>
#include<fstream>

#include"Worker.h"

using namespace std;

#define FILENAME "Ա����Ϣ.txt"

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

	//��¼�ļ��е���������
	int m_EmpNum;
	//Ա�������ָ��
	Worker** m_EmpArray;

	//����ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FilesEmpty;

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

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

	//����ְ��
	void Sort_Emp();

	//��պ���
	void Clean_File();
};
#endif // !WORKERMANAGER_H