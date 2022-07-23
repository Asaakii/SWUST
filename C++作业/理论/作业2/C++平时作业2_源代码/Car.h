#pragma once
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
//创建汽车类作为交通工具类的子类
class Car:virtual public Vehicle
{
protected:
	//座位数
	int seat_num;

public:
	Car();
	Car(int ms, int w, int seat);
	~Car();
	//输出信息函数
	virtual void display();
	//表示能够运动的函数
	virtual void Move();
	//表示能够停止的函数
	virtual void Stop();
};
#endif // !CAR_H
