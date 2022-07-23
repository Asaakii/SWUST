// P2.cpp: implementation of the CP2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "P2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP2::CP2()
{
	this->x=0;
	this->y=0;
}

CP2::~CP2()
{

}

CP2::CP2(int x0,int y0)
{
	this->x=x0;
	this->y=y0;
}

CP2::CP2(int x0,int y0,CRGB c0)
{
	this->x=x0;
	this->y=y0;
	this->c=c0;
}

