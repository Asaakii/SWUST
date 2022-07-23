#pragma once
#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include "Car.h"
#include "Bicycle.h"
//����Ħ�г���Ϊ����������г���Ĺ�ͬ����
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
