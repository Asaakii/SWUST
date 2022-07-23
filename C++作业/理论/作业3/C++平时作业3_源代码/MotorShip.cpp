#include <iostream>
#include "MotorShip.h"

using namespace std;

MotorShip::MotorShip()
{

}

MotorShip::MotorShip(int ms, int w, int h, int dep) :Bicycle(ms, w, h), Ship(ms, w, dep)
{
	cout << "执行摩托艇类带参数的构造函数" << endl;
}

void MotorShip::display()
{
	cout << "本类型是摩托艇" << endl;
}

void MotorShip::Move()
{
	cout << "摩托艇开始运行" << endl;
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "高度:" << height << endl;
	cout << "油耗:" << depletion << endl;
}

MotorShip::~MotorShip()
{
	cout << "执行摩托艇类析构函数" << endl;
}