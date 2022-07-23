#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

//创建交通工具的抽象类
class Vehicle
{
protected:
	//最高速度
	int max_speed;
	//重量
	int weight;
	//已行驶里程
	double mileage;

public:
	//不带参数的构造函数
	Vehicle();
	//带参数的构造函数（重载）
	Vehicle(int ms, int w);
	//析构函数
	virtual ~Vehicle();
	//运算符重载
	friend ostream& operator<<(ostream& out, const Vehicle& c);
	Vehicle operator+(double _mileage);
	Vehicle operator-(double _mileage);
	//纯虚函数
	virtual void display() = 0;
	virtual void Move() = 0;
};
#endif // !VEHICLE_H