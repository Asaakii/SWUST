#pragma once
#ifndef BOSS_H
#define BOSS_H

#include<iostream>

#include "Worker.h"

using namespace std;

//老板类
class Boss :public Worker
{
public:
	//构造函数
	Boss(int id, string name, string sex, int age, string idcard, float salary, int number);

	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();

	//析构函数
	~Boss();
};
#endif // !BOSS_H