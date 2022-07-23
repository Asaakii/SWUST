// CRGB.h: interface for the CRGB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_)
#define AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRGB  //��ɫ��
{
public:
	CRGB();
	CRGB(double,double,double);
	friend CRGB operator+(CRGB &,CRGB &);
	friend CRGB operator*(double,CRGB &);
	virtual ~CRGB();
public:
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
};

#endif // !defined(AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_)
