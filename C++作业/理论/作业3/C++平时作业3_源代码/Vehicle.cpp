#include "Vehicle.h"

Vehicle::Vehicle()
{

}

Vehicle::Vehicle(int ms, int w)
{
	max_speed = ms;
	weight = w;
}

ostream& operator<<(ostream& out, const Vehicle& c) //����ʵ��
{
	cout << "����ʻ��̣�" << c.mileage << "km" << endl;
}

Vehicle Vehicle::operator+(double _mileage)
{
	Vehicle sum(0.0);
	sum.mileage = mileage + _mileage;
	return sum;
}

Vehicle Vehicle::operator-(double _mileage)
{
	Vehicle sum(0.0);
	sum.mileage = mileage - _mileage;
	return sum;
}
Vehicle::~Vehicle()
{

}