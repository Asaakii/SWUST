#include <iostream>
#include "Ship.h"

using namespace std;

Ship::Ship()
{

}

Ship::Ship(int ms, int w, int dep) :Vehicle(ms, w)
{
	cout << "执行船舶类带参数的构造函数" << endl;
	depletion = dep;
}

void Ship::display()
{
	cout << "本类型是船舶类" << endl;
}

void Ship::Move()
{
	cout << "船开始运行" << endl;
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "油耗:" << depletion << endl;
}

Ship::~Ship()
{
	cout << "执行船舶类析构函数" << endl;
}