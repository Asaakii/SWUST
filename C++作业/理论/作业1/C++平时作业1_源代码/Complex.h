#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
private:
	double real;				//实部
	double imag;				//虚部
public:
	Complex();					//构造函数
	Complex(double r, double i);//构造函数的重载
	~Complex();					//析构函数
	void show();				//输出
	Complex operator+(const Complex& c);	//复数加法
	Complex operator-(const Complex& c);	//复数减法
	Complex& operator=(const Complex& c);	//赋值运算符重载
};
#endif // !COMPLEX_H