#include <iostream>
#include "Ship.h"

using namespace std;

Ship::Ship()
{

}

Ship::Ship(int ms, int w, int dep) :Vehicle(ms, w)
{
	cout << "ִ�д�����������Ĺ��캯��" << endl;
	depletion = dep;
}

void Ship::display()
{
	cout << "�������Ǵ�����" << endl;
}

void Ship::Move()
{
	cout << "����ʼ����" << endl;
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�ͺ�:" << depletion << endl;
}

Ship::~Ship()
{
	cout << "ִ�д�������������" << endl;
}