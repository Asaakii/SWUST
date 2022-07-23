#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

using namespace std;
//创建交通工具的抽象类
class Vehicle
{
protected:
	//最高速度
	int max_speed;
	//重量
	int weight;

public:
	//不带参数的构造函数
	Vehicle();
	//带参数的构造函数（重载）
	Vehicle(int ms, int w);
	//析构函数
	~Vehicle();
};
#endif // !VEHICLE_H