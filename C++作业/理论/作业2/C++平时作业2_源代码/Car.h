#pragma once
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
//������������Ϊ��ͨ�����������
class Car:virtual public Vehicle
{
protected:
	//��λ��
	int seat_num;

public:
	Car();
	Car(int ms, int w, int seat);
	~Car();
	//�����Ϣ����
	virtual void display();
	//��ʾ�ܹ��˶��ĺ���
	virtual void Move();
	//��ʾ�ܹ�ֹͣ�ĺ���
	virtual void Stop();
};
#endif // !CAR_H
