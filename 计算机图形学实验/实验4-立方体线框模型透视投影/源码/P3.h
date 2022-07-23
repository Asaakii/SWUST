// P3.h: interface for the CP3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_)
#define AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RGB.h"

class CP3  //»˝Œ¨µ„¿‡
{
public:
	CP3();
	virtual ~CP3();
	CP3(double,double,double);
	CP3(double,double,double,CRGB);
public:
	double x;
	double y;
	double z;
	CRGB c;
};

#endif // !defined(AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_)
