#include <iostream>
#include "Bicycle.h"

using namespace std;

Bicycle::Bicycle()
{

}

Bicycle::Bicycle(int ms, int w, int h) :Vehicle(ms, w)
{
	cout << "ִ�����г���������Ĺ��캯��" << endl;
	height = h;
}

void Bicycle::display()
{
	cout << "�����������г���" << endl;
}

void Bicycle::Move()
{
	cout << "���г���ʼ����" << endl;
	cout << "����ٶ�:" << max_speed << endl;
	cout << "����:" << weight << endl;
	cout << "�߶�:" << height << endl;
}

Bicycle::~Bicycle()
{
	cout << "ִ�����г�����������" << endl;
}