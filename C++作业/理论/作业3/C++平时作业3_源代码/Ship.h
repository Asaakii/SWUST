#pragma once
#ifndef SHIP_H
#define SHIP_H

#include "Vehicle.h"
//����������Ϊ��ͨ�����������
class Ship :virtual public Vehicle
{
protected:
	//������
	int depletion;

public:
	Ship();
	Ship(int ms, int w, int dep);
	virtual ~Ship();
	virtual void display();
	virtual void Move();
};
#endif // !SHIP_H
