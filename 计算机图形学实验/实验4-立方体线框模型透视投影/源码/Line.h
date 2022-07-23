// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_)
#define AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"

class CLine  //ֱ����
{
public:
	CLine();
	virtual ~CLine();
    void MoveTo(CDC *,CP2);//�ƶ���ָ��λ��
	void MoveTo(CDC *,int,int,CRGB);//���غ���
	void LineTo(CDC *,CP2);//ͨ��ֱ�ߵ�����Bresenham�㷨,�������յ�����
	void LineTo(CDC *,int,int,CRGB);//���غ���
	CRGB Interpolation(int,int,int,CRGB,CRGB);//���Բ�ֵ
	int Sign(int);//����-1��0��1���Ա���Ϊ<0,=0,>0
public:
	CP2 P1;//ֱ���������
	CP2 P2;//ֱ���յ�����
};

#endif // !defined(AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_)
