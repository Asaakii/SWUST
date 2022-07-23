// CRGB.h: interface for the CRGB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_)
#define AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRGB  //颜色类
{
public:
	CRGB();
	CRGB(double,double,double);
	friend CRGB operator+(CRGB &,CRGB &);
	friend CRGB operator*(double,CRGB &);
	virtual ~CRGB();
public:
	double red;//红色分量
	double green;//绿色分量
	double blue;//蓝色分量
};

#endif // !defined(AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_)
