#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

//������ͨ���ߵĳ�����
class Vehicle
{
protected:
	//����ٶ�
	int max_speed;
	//����
	int weight;
	//����ʻ���
	double mileage;

public:
	//���������Ĺ��캯��
	Vehicle();
	//�������Ĺ��캯�������أ�
	Vehicle(int ms, int w);
	//��������
	virtual ~Vehicle();
	//���������
	friend ostream& operator<<(ostream& out, const Vehicle& c);
	Vehicle operator+(double _mileage);
	Vehicle operator-(double _mileage);
	//���麯��
	virtual void display() = 0;
	virtual void Move() = 0;
};
#endif // !VEHICLE_H