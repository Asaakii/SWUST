#include "Bicycle.h"

Bicycle::Bicycle()
{

}

Bicycle::Bicycle(int ms, int w, int h) :Vehicle(ms, w)
{
	height = h;
}

void Bicycle::display()
{
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�߶�:" << height << endl;
}

void Bicycle::Move()
{
	cout << "���г���ʼ����" << endl;
}

void Bicycle::Stop()
{
	cout << "���г�ֹͣ����" << endl;
	cout << endl;
}

Bicycle::~Bicycle()
{

}