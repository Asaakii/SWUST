#include "Car.h"

Car::Car()
{

}

Car::Car(int ms, int w, int seat) :Vehicle(ms, w) 
{ 
	seat_num = seat;
}

void Car::display()
{
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "��λ��:" << seat_num << endl;
}

void Car::Move()
{
	cout << "������ʼ����" << endl;
}

void Car::Stop()
{
	cout << "����ֹͣ����" << endl;
	cout << endl;
}

Car::~Car()
{

}