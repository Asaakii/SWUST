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
	virtual ~Bicycle();
	virtual void display();
	virtual void Move();
};
#endif // !BICYCLE_H
