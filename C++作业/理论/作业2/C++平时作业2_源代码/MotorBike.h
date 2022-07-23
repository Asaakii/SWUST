#pragma once
#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include "Car.h"
#include "Bicycle.h"
//创建摩托车类为汽车类和自行车类的共同子类
class MotorBike :public Bicycle, public Car
{
public:
	MotorBike();
	MotorBike(int ms, int w, int h, int seat);
	~MotorBike();
	virtual void display();
	virtual void Move();
	virtual void Stop();
};
#endif // !MOTORBIKE_H
