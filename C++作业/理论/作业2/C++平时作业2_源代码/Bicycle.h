#pragma once
#ifndef BICYCLE_H
#define BICYCLE_H

#include "Vehicle.h"
//�������г���Ϊ��ͨ�����������
class Bicycle :virtual public Vehicle
{
protected:
	//�߶�
	int height;

public:
	Bicycle();
	Bicycle(int ms, int w, int h);
	~Bicycle();
	virtual void display();
	virtual void Move();
	virtual void Stop();
};
#endif // !BICYCLE_H
