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
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�ͺ�:" << depletion << endl;
}

void Ship::Move()
{
	cout << "����ʼ����" << endl;
}

void Ship::Stop()
{
	cout << "��ֹͣ����" << endl;
	cout << endl;
}

Ship::~Ship()
{

}