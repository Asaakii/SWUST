#include <iostream>
#include <list> 
#include <vector>
#include <numeric> 
#include <algorithm> 

#include "Vehicle.h"
#include "Car.h"
#include "Bicycle.h"
#include "Ship.h"
#include "MotorBike.h"
#include "MotorShip.h"

using namespace std;

//����һ��list������ʵ��CAR
typedef list<int> CAR;
//����һ��list������ʵ��BICYCLE
typedef list<int> BICYCLE;
//����һ��list������ʵ��SHIP
typedef list<int> SHIP;
//����һ��vector������ʵ��MOTORBIKE
typedef vector<int> MOTORBIKE;
//����һ��vector������ʵ��MOTORSHIP
typedef vector<int> MOTORSHIP;

void UseVehicle(Vehicle* _ptr_vehicle)
{
	//ȫ�ֺ���������Ϊָ��������ָ�룬
	//���ô��麯��ʵ�ֻ��ڶ�̬����Ķ�̬����
	_ptr_vehicle->display();
	cout << "ptr_vehicle->Move()=";
	cout << _ptr_vehicle->Move() << endl;
}

int main()
{
	Vehicle* ptr_vehicle = NULL;

	cout << "ʵ����Car�����_car�������麯��Move():" << endl;
	Car _car(300, 900, 4);
	cout << _car.Move() << endl;
	Car* ptr_car = &_car;

	cout << "ʵ����Bicycle�����_bicycle�������麯��Move():" << endl;
	Bicycle _bicycle(40, 20, 120);
	cout << _bicycle.Move() << endl;
	Bicycle* ptr_bicycle = &_bicycle;

	cout << "ʵ����Ship�����_ship�������麯��Move():" << endl;
	Ship _ship(60, 200, 300);
	cout << _ship.Move() << endl;
	Ship* ptr_ship = &_ship;

	cout << "ʵ����MotorBike�����_motorbike�������麯��Move():" << endl;
	MotorBike _motorbike(100, 150, 100, 2);
	cout << _motorbike.Move() << endl;
	MotorBike* ptr_motorbike = &_motorbike;

	cout << "ʵ����MotorShip�����_motorship�������麯��Move():" << endl;
	MotorShip _motorship(80, 100, 60, 500);
	cout << _motorship.Move() << endl;
	MotorShip* ptr_motorship = &_motorship;

	cout << "ͨ���������ָ�룬���ô��麯���ӿ�,ʵ�ֶ�̬��" << endl;
	UseVehicle(ptr_car);
	UseVehicle(ptr_bicycle);
	UseVehicle(ptr_ship);
	UseVehicle(ptr_motorbike);
	UseVehicle(ptr_motorship);

	cout << "��ʾ����ʾSTL����list���÷���" << endl;
	//��CAR����һ����ΪlistCar��list���� 
	CAR listCar;
	//����aΪ������ 
	CAR::iterator a;
	//��ǰ����listCar������������� 
	listCar.push_front('1000');
	listCar.push_front('100');
	//��ǰ�����ʾlistCar�е����� 
	cout << "listCar.begin()---listTwo.end():" << endl;
	for (a = listCar.begin(); a != listCar.end(); ++a)
		cout << char(*a) << " ";
	cout << endl;

	//��BICYCLE����һ����ΪlistBicycle��list���� 
	BICYCLE listBicycle;
	//����bΪ������ 
	BICYCLE::iterator b;
	//��ǰ����listBicycle������������� 
	listBicycle.push_front('100');
	listBicycle.push_front('10');
	//��ǰ�����ʾlistBicycle�е����� 
	cout << "listBicycle.begin()---listBicycle.end():" << endl;
	for (b = listBicycle.begin(); b != listBicycle.end(); ++b)
		cout << char(*b) << " ";
	cout << endl;

	//��SHIP����һ����ΪlistCShip��list���� 
	SHIP listShip;
	//����cΪ������ 
	SHIP::iterator c;
	//��ǰ����listShip������������� 
	listShip.push_front('500');
	listShip.push_front('50');
	//��ǰ�����ʾlistShip�е�����
	cout << "listShip.begin()---listShip.end():" << endl;
	for (c = listShip.begin(); c != listShip.end(); ++c)
		cout << char(*c) << " ";
	cout << endl;


	cout << "��ʾ����ʾSTL����vector���÷�" << endl;
	vector<int> vehicle = { 100,150,80 };
	auto res = find(vehicle.begin(), vehicle.end(), 100);
	if (res == vehicle.end()) 
	{
		cout << "û���ҵ�Ԫ��" << endl;
	}
	else 
	{
		cout << "�ҵ�Ԫ��" << *res << endl;
	}

	return 0;
}