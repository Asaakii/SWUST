#include <iostream>
#include "MotorShip.h"

using namespace std;

MotorShip::MotorShip()
{

}

MotorShip::MotorShip(int ms, int w, int h, int dep) :Bicycle(ms, w, h), Ship(ms, w, dep)
{
	cout << "ִ��Ħ��ͧ��������Ĺ��캯��" << endl;
}

void MotorShip::display()
{
	cout << "��������Ħ��ͧ" << endl;
}

void MotorShip::Move()
{
	cout << "Ħ��ͧ��ʼ����" << endl;
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�߶�:" << height << endl;
	cout << "�ͺ�:" << depletion << endl;
}

MotorShip::~MotorShip()
{
	cout << "ִ��Ħ��ͧ����������" << endl;
}