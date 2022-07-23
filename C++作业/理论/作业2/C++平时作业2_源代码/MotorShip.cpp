#include "MotorShip.h"

MotorShip::MotorShip()
{

}

MotorShip::MotorShip(int ms, int w, int h, int dep) :Bicycle(ms, w, h), Ship(ms, w, dep)
{

}

void MotorShip::display()
{
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "高度:" << height << endl;
	cout << "油耗:" << depletion << endl;
}

void MotorShip::Move()
{
	cout << "摩托艇开始运行" << endl;
}

void MotorShip::Stop()
{
	cout << "摩托艇停止运行" << endl;
	cout << endl;
}

MotorShip::~MotorShip()
{

}