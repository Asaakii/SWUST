#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
private:
	double real;				//ʵ��
	double imag;				//�鲿
public:
	Complex();					//���캯��
	Complex(double r, double i);//���캯��������
	~Complex();					//��������
	void show();				//���
	Complex operator+(const Complex& c);	//�����ӷ�
	Complex operator-(const Complex& c);	//��������
	Complex& operator=(const Complex& c);	//��ֵ���������
};
#endif // !COMPLEX_H