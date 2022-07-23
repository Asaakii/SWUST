#include "Vehicle.h"
#include "Car.h"
#include "Bicycle.h"
#include "Ship.h"
#include "MotorBike.h"
#include "MotorShip.h"

int main()
{
	Car ca(300, 900, 4);
	ca.Move();
	ca.display();
	ca.Stop();

	Bicycle bi(40, 20, 120);
	bi.Move();
	bi.display();
	bi.Stop();

	Ship sh(60, 200, 300);
	sh.Move();
	sh.display();
	sh.Stop();

	MotorBike mob(100, 150, 100, 2);
	mob.Move();
	mob.display();
	mob.Stop();

	MotorShip mos(80, 100, 60, 500);
	mos.Move();
	mos.display();
	mos.Stop();
	return 0;
}