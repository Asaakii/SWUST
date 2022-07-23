// CRGB.cpp: implementation of the CRGB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "RGB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRGB::CRGB()
{
	red=1.0;
	green=1.0;
	blue=1.0;
}
CRGB::CRGB(double r,double g,double b)//重载构造函数
{
	red=r;
	green=g;
	blue=b;
}

CRGB::~CRGB()
{

}

CRGB operator +(const CRGB &c1,const CRGB &c2)//+运算符重载
{
	CRGB c;
	c.red=c1.red+c2.red;
	c.green=c1.green+c2.green;
	c.blue=c1.blue+c2.blue;
	return c;
}

CRGB operator -(const CRGB &c1,const CRGB &c2)//-运算符重载
{
	CRGB c;
	c.red=c1.red-c2.red;
	c.green=c1.green-c2.green;
	c.blue=c1.blue-c2.blue;
	return c;
}

CRGB operator *(const CRGB &c1,const CRGB &c2)//*运算符重载
{
	CRGB c;
	c.red=c1.red*c2.red;
	c.green=c1.green*c2.green;
	c.blue=c1.blue*c2.blue;
	return c;
}

CRGB operator *(const CRGB &c1,double k)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}

CRGB operator *(double k,const CRGB &c1)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}

CRGB operator /(const CRGB &c1,double k)///运算符重载
{
   CRGB c;
   c.red=c1.red/k;
   c.green=c1.green/k;
   c.blue=c1.blue/k;
   return c;
}

CRGB operator +=(CRGB &c1,CRGB &c2)//+=运算符重载
{
	c1.red=c1.red+c2.red;
	c1.green=c1.green+c2.green;
	c1.blue=c1.blue+c2.blue;
	return c1;
}

CRGB operator -=(CRGB &c1,CRGB &c2)//-=运算符重载
{
	c1.red=c1.red-c2.red;
	c1.green=c1.green-c2.green;
	c1.blue=c1.blue-c2.blue;
	return c1;
}

CRGB operator *=(CRGB &c1,CRGB &c2)//*=运算符重载
{
	c1.red=c1.red*c2.red;
	c1.green=c1.green*c2.green;
	c1.blue=c1.blue*c2.blue;
	return c1;
}

CRGB operator /=(CRGB &c1,double k)///=运算符重载
{
	c1.red=c1.red/k;
	c1.green=c1.green/k;
	c1.blue=c1.blue/k;
	return c1;
}

void CRGB::Normalize()//归一化
{
	red=(red < 0.0) ? 0.0 : ((red > 1.0) ? 1.0 : red);
	green=(green < 0.0) ? 0.0 : ((green > 1.0) ? 1.0 : green);
	blue=(blue < 0.0) ? 0.0 : ((blue > 1.0) ? 1.0 : blue);
}

