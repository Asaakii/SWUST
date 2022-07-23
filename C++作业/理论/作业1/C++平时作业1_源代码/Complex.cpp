#include <iostream>

#include "Complex.h"

using namespace std;

Complex::Complex()//���캯��
{

}

Complex::Complex(double r, double i)
{
	real = r;
	imag = i;
}

Complex::~Complex()//��������
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
	if (imag > 0)//�鲿����0
	{
		cout << real << '+' << imag << "*i" << endl;
	}
	else if (imag == 0)//�鲿����0
	{
		cout << real << endl;
	}
	else if (imag < 0)//�鲿С��0
	{
		cout << real << imag << "*i" << endl;
	}
}

Complex Complex::operator+(const Complex& c)//�ӷ�����
{
	Complex a;
	a.real = real + c.real;
	a.imag = imag + c.imag;
	cout << "���������Ϊ��";
	return a;
}
Complex Complex::operator-(const Complex& c)//��������
{
	Complex a;
	a.real = real - c.real;
	a.imag = imag - c.imag;
	cout << "���������Ϊ��";
	return a;
}