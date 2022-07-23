#include "Car.h"

Car::Car()
{

}

Car::Car(int ms, int w, int seat) :Vehicle(ms, w) 
{ 
	seat_num = seat;
}

void Car::display()
{
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "座位数:" << seat_num << endl;
}

void Car::Move()
{
	cout << "汽车开始运行" << endl;
}

void Car::Stop()
{
	cout << "汽车停止运行" << endl;
	cout << endl;
}

Car::~Car()
{

}