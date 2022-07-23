// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Vector.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()//z轴正向
{
	x=0.0;
	y=0.0;
	z=1.0;
}

CVector::~CVector()
{

}

CVector::CVector(const CP3 &p)
{
	x=p.x;
	y=p.y;
	z=p.z;
}

CVector::CVector(double x,double y,double z)
{
	this->x=x;
	this->y=y;
	this->z=z;	
}

CVector::CVector(const CP3 &p0,const CP3 &p1)
{
	x=p1.x-p0.x;
	y=p1.y-p0.y;
	z=p1.z-p0.z;
}

double CVector::Mag()//矢量的模
{
	return sqrt(x*x+y*y+z*z);
}

CVector CVector::Normalize()//归一化到单位矢量
{
	CVector vector;
	double Mag=sqrt(x*x+y*y+z*z);
	if(fabs(Mag)<1e-6)
		Mag=1.0;
	vector.x=x/Mag;
	vector.y=y/Mag;
	vector.z=z/Mag;
	return vector;
}

CVector operator +(const CVector &v0,const CVector &v1)//矢量的和
{
	CVector vector;
	vector.x=v0.x+v1.x;
	vector.y=v0.y+v1.y;
	vector.z=v0.z+v1.z;
	return vector;
}

CVector operator -(const CVector &v0,const CVector &v1)//矢量的差
{
	CVector vector;
	vector.x=v0.x-v1.x;
	vector.y=v0.y-v1.y;
	vector.z=v0.z-v1.z;
	return vector;
}

CVector operator *(const CVector &v,double k)//矢量与常量的积
{
	CVector vector;
	vector.x=v.x*k;
	vector.y=v.y*k;
	vector.z=v.z*k;
	return vector;
}

CVector operator *(double k,const CVector &v)//常量与矢量的积
{
	CVector vector;
	vector.x=v.x*k;
	vector.y=v.y*k;
	vector.z=v.z*k;
	return vector;
}

CVector operator /(const CVector &v,double k)//矢量数除
{
	if(fabs(k)<1e-6)
		k=1.0;
	CVector vector;
	vector.x=v.x/k;
	vector.y=v.y/k;
	vector.z=v.z/k;
	return vector;
}

CVector operator +=(CVector &v0,CVector &v1)//+=运算符重载
{
	v1.x=v0.x+v1.x;
	v1.y=v0.y+v1.y;
	v1.z=v0.z+v1.z;
	return v1;
}

CVector operator -=(CVector &v0,CVector &v1)//-=运算符重载
{
	v0.x=v0.x-v1.x;
	v0.y=v0.y-v1.y;
	v0.z=v0.z-v1.z;
	return v0;
}

CVector operator *=(CVector &v0,CVector &v1)//*=运算符重载
{
	v0.x=v0.x*v1.x;
	v0.y=v0.y*v1.y;
	v0.z=v0.z*v1.z;
	return v0;
}

CVector operator /=(CVector &v,double k)///=运算符重载
{
	v.x=v.x/k;
	v.y=v.y/k;
	v.z=v.z/k;
	return v;
}

double Dot(const CVector &v0,const CVector &v1)//矢量的点积
{
	return(v0.x*v1.x+v0.y*v1.y+v0.z*v1.z);
}

CVector Cross(const CVector &v0,const CVector &v1)//矢量的叉积
{
	CVector vector;
	vector.x=v0.y*v1.z-v0.z*v1.y;
	vector.y=v0.z*v1.x-v0.x*v1.z;
	vector.z=v0.x*v1.y-v0.y*v1.x;
	return vector;
}

