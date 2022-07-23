#pragma once
#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include<iostream>
#include<fstream>

#include"Worker.h"

using namespace std;

#define FILENAME "员工信息.txt"

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//析构函数
	~WorkerManager();

	//展示菜单
	void Show_Menu();

	//退出管理程序
	void ExitSystem();

	//记录文件中的人数个数
	int m_EmpNum;
	//员工数组的指针
	Worker** m_EmpArray;

	//增加职工
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空 标志
	bool m_FilesEmpty;

	//统计人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//按照职工编号判断职工是否存在
	int IsExist(int id);

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空函数
	void Clean_File();
};
#endif // !WORKERMANAGER_H