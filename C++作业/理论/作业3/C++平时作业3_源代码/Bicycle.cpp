#include <iostream>
#include "Bicycle.h"

using namespace std;

Bicycle::Bicycle()
{

}

Bicycle::Bicycle(int ms, int w, int h) :Vehicle(ms, w)
{
	cout << "执行自行车类带参数的构造函数" << endl;
	height = h;
}

void Bicycle::display()
{
	cout << "本类型是自行车类" << endl;
}

void Bicycle::Move()
{
	cout << "自行车开始运行" << endl;
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "高度:" << height << endl;
}

Bicycle::~Bicycle()
{
	cout << "执行自行车类析构函数" << endl;
}