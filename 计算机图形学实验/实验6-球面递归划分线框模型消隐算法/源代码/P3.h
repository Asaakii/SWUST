// P3.h: interface for the CP3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_)
#define AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"

class CP3:public CP2
{
public:
	CP3();
	virtual ~CP3();
	CP3(double,double,double);
	friend CP3 operator +(const CP3 &,const CP3 &);//运算符重载
	friend CP3 operator -(const CP3 &,const CP3 &);
	friend CP3 operator *(const CP3 &,double);
	friend CP3 operator *(double,const CP3 &);
	friend CP3 operator /(const CP3 &,double);
	friend CP3 operator+=(CP3 &,CP3 &);
	friend CP3 operator-=(CP3 &,CP3 &);
	friend CP3 operator*=(CP3 &,double);
	friend CP3 operator/=(CP3 &,double);
	double Mag();//长度
public:
	double z;
};

#endif // !defined(AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_)
