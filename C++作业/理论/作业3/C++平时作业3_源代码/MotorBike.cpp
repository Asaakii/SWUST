#include <iostream>
#include "MotorBike.h"

using namespace std;

MotorBike::MotorBike()
{

}

MotorBike::MotorBike(int ms, int w, int h, int seat) :Bicycle(ms, w, h), Car(ms, w, seat)
{
	cout << "ִ��Ħ�г���������Ĺ��캯��" << endl;
}

void MotorBike::display()
{
	cout << "��������Ħ�г�" << endl;
}

void MotorBike::Move()
{
	cout << "Ħ�г���ʼ����" << endl;
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�߶�:" << height << endl;
	cout << "��λ��:" << seat_num << endl;
}

MotorBike::~MotorBike()
{
	cout << "ִ��Ħ�г�����������" << endl;
}