#pragma once
#ifndef SHIP_H
#define SHIP_H

#include "Vehicle.h"
//创建船舶类为交通工具类的子类
class Ship :virtual public Vehicle
{
protected:
	//耗油量
	int depletion;

public:
	Ship();
	Ship(int ms, int w, int dep);
	virtual ~Ship();
	virtual void display();
	virtual void Move();
};
#endif // !SHIP_H
