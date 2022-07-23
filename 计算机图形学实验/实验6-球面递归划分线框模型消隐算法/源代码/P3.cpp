// P3.cpp: implementation of the CP3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "P3.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP3::CP3()
{
	z=0.0;
}

CP3::~CP3()
{

}
CP3::CP3(double x,double y,double z):CP2(x,y)
{
	this->z=z;
}

CP3 operator +(const CP3 &p0,const CP3 &p1)//和
{	
	CP3 p;
	p.x=p0.x+p1.x;
	p.y=p0.y+p1.y;
	p.z=p0.z+p1.z;
	return p;
}

CP3 operator -(const CP3 &p0,const CP3 &p1)//差
{
	CP3 p;
	p.x=p0.x-p1.x;
	p.y=p0.y-p1.y;
	p.z=p0.z-p1.z;
	return p;
}

CP3 operator *(const CP3 &p,double k)//点和常量的积
{	
	return CP3(p.x*k,p.y*k,p.z*k);
}

CP3 operator *(double k,const CP3 &p)//点和常量的积
{	
	return CP3(p.x*k,p.y*k,p.z*k);
}

CP3 operator /(const CP3 &p0,double k)//数除
{
	if(fabs(k)<1e-6)
		k=1.0;
	CP3 p;
	p.x=p0.x/k;
	p.y=p0.y/k;
	p.z=p0.z/k;
	return p;
}

CP3 operator+=(CP3 &p0,CP3 &p1)
{
	p0.x=p0.x+p1.x;
	p0.y=p0.y+p1.y;
	p0.z=p0.z+p1.z;
	return p0;
}

CP3 operator-=(CP3 &p0,CP3 &p1)
{
	p0.x=p0.x-p1.x;
	p0.y=p0.y-p1.y;
	p0.z=p0.z-p1.z;
	return p0;
}

CP3 operator*=(CP3 &p0,double k)
{
	p0.x=p0.x*k;
	p0.y=p0.y*k;
	p0.z=p0.z*k;
	return p0;
}

CP3 operator/=(CP3 &p0,double k)
{
	if(fabs(k)<1e-6)
		k=1.0;
	p0.x=p0.x/k;
	p0.y=p0.y/k;
	p0.z=p0.z/k;
	return p0;
}

double CP3::Mag()//长度
{
	return sqrt(x*x+y*y+z*z);
}

