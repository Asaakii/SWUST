#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

using namespace std;
//������ͨ���ߵĳ�����
class Vehicle
{
protected:
	//����ٶ�
	int max_speed;
	//����
	int weight;

public:
	//���������Ĺ��캯��
	Vehicle();
	//�������Ĺ��캯�������أ�
	Vehicle(int ms, int w);
	//��������
	~Vehicle();
};
#endif // !VEHICLE_H