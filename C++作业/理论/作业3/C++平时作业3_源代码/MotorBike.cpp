#include <iostream>
#include "MotorBike.h"

using namespace std;

MotorBike::MotorBike()
{

}

MotorBike::MotorBike(int ms, int w, int h, int seat) :Bicycle(ms, w, h), Car(ms, w, seat)
{
	cout << "执行摩托车类带参数的构造函数" << endl;
}

void MotorBike::display()
{
	cout << "本类型是摩托车" << endl;
}

void MotorBike::Move()
{
	cout << "摩托车开始运行" << endl;
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "高度:" << height << endl;
	cout << "座位数:" << seat_num << endl;
}

MotorBike::~MotorBike()
{
	cout << "执行摩托车类析构函数" << endl;
}