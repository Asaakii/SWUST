#include <iostream>
#include "Car.h"

using namespace std;

Car::Car()
{

}

Car::Car(int ms, int w, int seat) :Vehicle(ms, w)
{
	cout << "执行汽车类带参数的构造函数" << endl;
	seat_num = seat;
}

void Car::display()
{
	cout << "本类型是汽车类" << endl;
}

void Car::Move()
{
	cout << "汽车开始运行" << endl;
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "座位数:" << seat_num << endl;
}

Car::~Car()
{
	cout << "执行汽车类析构函数" << endl;
}