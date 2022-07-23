#pragma once
#ifndef MOTORSHIP_H
#define MOTOESHIP_H

#include "Bicycle.h"
#include "Ship.h"
//创建摩托艇类为自行车类和船舶类的共同子类
class MotorShip :public Bicycle, public Ship
{
public:
	MotorShip();
	MotorShip(int ms, int w, int h, int dep);
	virtual ~MotorShip();
	virtual void display();
	virtual void Move();
};
#endif // !MOTORSHIP_H