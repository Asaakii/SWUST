#pragma once
#ifndef MOTORSHIP_H
#define MOTOESHIP_H

#include "Bicycle.h"
#include "Ship.h"
//����Ħ��ͧ��Ϊ���г���ʹ�����Ĺ�ͬ����
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