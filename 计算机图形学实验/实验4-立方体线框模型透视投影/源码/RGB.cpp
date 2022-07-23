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
	this->red=0.0;
	this->green=0.0;
	this->blue=0.0;
}
CRGB::CRGB(double r,double g,double b)//重载构造函数
{
	this->red=r;
	this->green=g;
	this->blue=b;
}

CRGB::~CRGB()
{

}

CRGB operator +(CRGB &c1,CRGB &c2)//+运算符重载
{
	CRGB c;
	c.red=c1.red+c2.red;
	c.green=c1.green+c2.green;
	c.blue=c1.blue+c2.blue;
	return c;
}
CRGB operator *(double k,CRGB &c1)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}

