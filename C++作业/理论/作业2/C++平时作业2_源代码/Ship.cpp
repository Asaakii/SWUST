#include "Ship.h"

Ship::Ship()
{

}

Ship::Ship(int ms, int w, int dep) :Vehicle(ms, w)
{
	depletion = dep;
}

void Ship::display()
{
	cout << "最高速度:" << max_speed << endl;
	cout << "重量:" << weight << endl;
	cout << "油耗:" << depletion << endl;
}

void Ship::Move()
{
	cout << "船开始运行" << endl;
}

void Ship::Stop()
{
	cout << "船停止运行" << endl;
	cout << endl;
}

Ship::~Ship()
{

}