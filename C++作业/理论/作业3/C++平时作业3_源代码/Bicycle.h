#pragma once
#ifndef BICYCLE_H
#define BICYCLE_H

#include "Vehicle.h"
//创建自行车类为交通工具类的子类
class Bicycle :virtual public Vehicle
{
protected:
	//高度
	int height;

public:
	Bicycle();
	Bicycle(int ms, int w, int h);
	virtual ~Bicycle();
	virtual void display();
	virtual void Move();
};
#endif // !BICYCLE_H
