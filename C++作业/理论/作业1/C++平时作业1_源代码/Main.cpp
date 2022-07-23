#include <iostream>

#include "Complex.h"

using namespace std;

int main()
{
	Complex c1(1, -2);
	Complex c2(2, 3);
	c1.show();
	c2.show();

	Complex cAdd = c1.operator +(c2);
	cAdd.show();

	Complex cSub = c1.operator -(c2);
	cSub.show();

	return 0;
}