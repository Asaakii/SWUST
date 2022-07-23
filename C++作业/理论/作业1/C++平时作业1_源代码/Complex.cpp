#include <iostream>

#include "Complex.h"

using namespace std;

Complex::Complex()//构造函数
{

}

Complex::Complex(double r, double i)
{
	real = r;
	imag = i;
}

Complex::~Complex()//析构函数
{

}

Complex& Complex::operator=(const Complex& c)
{
	this->real = c.real;
	this->imag = c.imag * (-1);
	return *this;
}

void Complex::show()
{
	if (imag > 0)//虚部大于0
	{
		cout << real << '+' << imag << "*i" << endl;
	}
	else if (imag == 0)//虚部等于0
	{
		cout << real << endl;
	}
	else if (imag < 0)//虚部小于0
	{
		cout << real << imag << "*i" << endl;
	}
}

Complex Complex::operator+(const Complex& c)//加法函数
{
	Complex a;
	a.real = real + c.real;
	a.imag = imag + c.imag;
	cout << "两复数相加为：";
	return a;
}
Complex Complex::operator-(const Complex& c)//减法函数
{
	Complex a;
	a.real = real - c.real;
	a.imag = imag - c.imag;
	cout << "两复数相减为：";
	return a;
}