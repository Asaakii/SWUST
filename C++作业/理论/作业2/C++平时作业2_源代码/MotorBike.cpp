#include "MotorBike.h"

MotorBike::MotorBike()
{

}

MotorBike::MotorBike(int ms, int w, int h, int seat) :Bicycle(ms, w, h), Car(ms, w, seat)
{

}

void MotorBike::display()
{
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�߶�:" << height << endl;
	cout << "��λ��:" << seat_num << endl;
}

void MotorBike::Move()
{
	cout << "Ħ�г���ʼ����" << endl;
}

void MotorBike::Stop()
{
	cout << "Ħ�г�ֹͣ����" << endl;
	cout << endl;
}

MotorBike::~MotorBike()
{

}