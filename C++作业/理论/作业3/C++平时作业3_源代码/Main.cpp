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

//创建一个list容器的实例CAR
typedef list<int> CAR;
//创建一个list容器的实例BICYCLE
typedef list<int> BICYCLE;
//创建一个list容器的实例SHIP
typedef list<int> SHIP;
//创建一个vector容器的实例MOTORBIKE
typedef vector<int> MOTORBIKE;
//创建一个vector容器的实例MOTORSHIP
typedef vector<int> MOTORSHIP;

void UseVehicle(Vehicle* _ptr_vehicle)
{
	//全局函数。参数为指向抽象基类指针，
	//调用纯虚函数实现基于动态联编的多态机制
	_ptr_vehicle->display();
	cout << "ptr_vehicle->Move()=";
	cout << _ptr_vehicle->Move() << endl;
}

int main()
{
	Vehicle* ptr_vehicle = NULL;

	cout << "实例化Car类对象_car并调用虚函数Move():" << endl;
	Car _car(300, 900, 4);
	cout << _car.Move() << endl;
	Car* ptr_car = &_car;

	cout << "实例化Bicycle类对象_bicycle并调用虚函数Move():" << endl;
	Bicycle _bicycle(40, 20, 120);
	cout << _bicycle.Move() << endl;
	Bicycle* ptr_bicycle = &_bicycle;

	cout << "实例化Ship类对象_ship并调用虚函数Move():" << endl;
	Ship _ship(60, 200, 300);
	cout << _ship.Move() << endl;
	Ship* ptr_ship = &_ship;

	cout << "实例化MotorBike类对象_motorbike并调用虚函数Move():" << endl;
	MotorBike _motorbike(100, 150, 100, 2);
	cout << _motorbike.Move() << endl;
	MotorBike* ptr_motorbike = &_motorbike;

	cout << "实例化MotorShip类对象_motorship并调用虚函数Move():" << endl;
	MotorShip _motorship(80, 100, 60, 500);
	cout << _motorship.Move() << endl;
	MotorShip* ptr_motorship = &_motorship;

	cout << "通过抽象基类指针，调用纯虚函数接口,实现多态：" << endl;
	UseVehicle(ptr_car);
	UseVehicle(ptr_bicycle);
	UseVehicle(ptr_ship);
	UseVehicle(ptr_motorbike);
	UseVehicle(ptr_motorship);

	cout << "本示例演示STL容器list的用法：" << endl;
	//用CAR创建一个名为listCar的list对象 
	CAR listCar;
	//声明a为迭代器 
	CAR::iterator a;
	//从前面向listCar容器中添加数据 
	listCar.push_front('1000');
	listCar.push_front('100');
	//从前向后显示listCar中的数据 
	cout << "listCar.begin()---listTwo.end():" << endl;
	for (a = listCar.begin(); a != listCar.end(); ++a)
		cout << char(*a) << " ";
	cout << endl;

	//用BICYCLE创建一个名为listBicycle的list对象 
	BICYCLE listBicycle;
	//声明b为迭代器 
	BICYCLE::iterator b;
	//从前面向listBicycle容器中添加数据 
	listBicycle.push_front('100');
	listBicycle.push_front('10');
	//从前向后显示listBicycle中的数据 
	cout << "listBicycle.begin()---listBicycle.end():" << endl;
	for (b = listBicycle.begin(); b != listBicycle.end(); ++b)
		cout << char(*b) << " ";
	cout << endl;

	//用SHIP创建一个名为listCShip的list对象 
	SHIP listShip;
	//声明c为迭代器 
	SHIP::iterator c;
	//从前面向listShip容器中添加数据 
	listShip.push_front('500');
	listShip.push_front('50');
	//从前向后显示listShip中的数据
	cout << "listShip.begin()---listShip.end():" << endl;
	for (c = listShip.begin(); c != listShip.end(); ++c)
		cout << char(*c) << " ";
	cout << endl;


	cout << "本示例演示STL容器vector的用法" << endl;
	vector<int> vehicle = { 100,150,80 };
	auto res = find(vehicle.begin(), vehicle.end(), 100);
	if (res == vehicle.end()) 
	{
		cout << "没有找到元素" << endl;
	}
	else 
	{
		cout << "找到元素" << *res << endl;
	}

	return 0;
}