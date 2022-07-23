// P2.h: interface for the CP2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P2_H__F5B8C5D7_BC9B_4346_817B_F55E89EE7598__INCLUDED_)
#define AFX_P2_H__F5B8C5D7_BC9B_4346_817B_F55E89EE7598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RGB.h"

class CP2  
{
public:
	CP2();
	virtual ~CP2();
	CP2(double,double);
	CP2(double,double,CRGB);	
public:
	double x;
	double y;
	CRGB c;
};

#endif // !defined(AFX_P2_H__F5B8C5D7_BC9B_4346_817B_F55E89EE7598__INCLUDED_)
