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
	~Ship();
	virtual void display();
	virtual void Move();
	virtual void Stop();
};
#endif // !SHIP_H
