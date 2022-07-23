#include "Bicycle.h"

Bicycle::Bicycle()
{

}

Bicycle::Bicycle(int ms, int w, int h) :Vehicle(ms, w)
{
	height = h;
}

void Bicycle::display()
{
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "高度:" << height << endl;
}

void Bicycle::Move()
{
	cout << "自行车开始运行" << endl;
}

void Bicycle::Stop()
{
	cout << "自行车停止运行" << endl;
	cout << endl;
}

Bicycle::~Bicycle()
{

}