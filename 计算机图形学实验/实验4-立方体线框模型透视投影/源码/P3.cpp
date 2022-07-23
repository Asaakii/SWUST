// P3.cpp: implementation of the CP3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "P3.h"

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
	this->x=0.0;
	this->y=0.0;
	this->z=0.0;
}

CP3::~CP3()
{

}

CP3::CP3(double x0,double y0,double z0)
{
	
	this->x=x0;
	this->y=y0;
	this->z=z0;
}

CP3::CP3(double x0,double y0,double z0,CRGB c0)
{
	this->x=x0;
	this->y=y0;
	this->z=z0;
	this->c=c0;
}