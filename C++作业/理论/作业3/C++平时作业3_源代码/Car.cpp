#include <iostream>
#include "Car.h"

using namespace std;

Car::Car()
{

}

Car::Car(int ms, int w, int seat) :Vehicle(ms, w)
{
	cout << "ִ��������������Ĺ��캯��" << endl;
	seat_num = seat;
}

void Car::display()
{
	cout << "��������������" << endl;
}

void Car::Move()
{
	cout << "������ʼ����" << endl;
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "��λ��:" << seat_num << endl;
}

Car::~Car()
{
	cout << "ִ����������������" << endl;
}