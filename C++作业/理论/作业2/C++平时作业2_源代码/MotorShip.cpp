#include "MotorShip.h"

MotorShip::MotorShip()
{

}

MotorShip::MotorShip(int ms, int w, int h, int dep) :Bicycle(ms, w, h), Ship(ms, w, dep)
{

}

void MotorShip::display()
{
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�߶�:" << height << endl;
	cout << "�ͺ�:" << depletion << endl;
}

void MotorShip::Move()
{
	cout << "Ħ��ͧ��ʼ����" << endl;
}

void MotorShip::Stop()
{
	cout << "Ħ��ֹͧͣ����" << endl;
	cout << endl;
}

MotorShip::~MotorShip()
{

}