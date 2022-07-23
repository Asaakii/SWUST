#include "MotorBike.h"

MotorBike::MotorBike()
{

}

MotorBike::MotorBike(int ms, int w, int h, int seat) :Bicycle(ms, w, h), Car(ms, w, seat)
{

}

void MotorBike::display()
{
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "高度:" << height << endl;
	cout << "座位数:" << seat_num << endl;
}

void MotorBike::Move()
{
	cout << "摩托车开始运行" << endl;
}

void MotorBike::Stop()
{
	cout << "摩托车停止运行" << endl;
	cout << endl;
}

MotorBike::~MotorBike()
{

}