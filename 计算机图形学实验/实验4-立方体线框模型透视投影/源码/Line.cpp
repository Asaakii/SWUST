// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Line.h"
#include "cmath"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{ 

}

CLine::~CLine()
{
	
}

void CLine::MoveTo(CDC *pDC,CP2 p1)//����ֱ����㺯��
{	
	P1=p1;
}

void CLine::MoveTo(CDC *pDC,int x1,int y1,CRGB c1)//���غ���
{	
	P1.x=x1,P1.y=y1;P1.c=c1;
}

void CLine::LineTo(CDC *pDC,CP2 p2)//ͨ��ֱ�ߵ�����Bresenham�㷨
{
	P2=p2;
	CP2 delt,p;
	bool InterChange=false;
	delt.x=abs(P2.x-P1.x);//��x
	delt.y=abs(P2.y-P1.y);//��y
	int e,s1,s2,Temp;//eΪ�����	
	s1=Sign(P2.x-P1.x);
    s2=Sign(P2.y-P1.y);
	if(delt.x<delt.y)
	{
		Temp=delt.x;
		delt.x=delt.y;
		delt.y=Temp;
        InterChange=true;//y����Ϊ��λ�Ʒ���
	}
	e=2*delt.y-delt.x;p=P1;//e=k-1/2��kΪֱ�ߵ�б��,��e=2��x��e�任ʵ�������㷨
	for(int i=0;i<delt.x;i++)//ֱ�߲������յ�����
	{
		if(InterChange)
			p.c=Interpolation(p.y,P1.y,P2.y,P1.c,P2.c);//y������ɫ���Բ�ֵ
		else
			p.c=Interpolation(p.x,P1.x,P2.x,P1.c,P2.c);//x������ɫ���Բ�ֵ
		pDC->SetPixel(p.x,p.y,RGB(p.c.red*255,p.c.green*255,p.c.blue*255));
		if(e>0)
		{
			if(InterChange)
				p.x+=s1;
			else
				p.y+=s2;
             e-=2*delt.x;//e=e-1
		}
		if(InterChange)
			p.y+=s2;
		else 
			p.x+=s1;
		e+=2*delt.y;//e=e+k		
	}
	P1=p2;
}

void CLine::LineTo(CDC *pDC,int x2,int y2,CRGB c2)//���غ���
{
	LineTo(pDC,CP2(x2,y2,c2));
}

CRGB CLine::Interpolation(int t,int t1,int t2,CRGB c1,CRGB c2)//���Բ�ֵ
{
	CRGB c;
	c=double(t-t2)/(t1-t2)*c1+double(t-t1)/(t2-t1)*c2;
	return c;
}

int CLine::Sign(int m)//����-1��0��1���Ա���Ϊ<0,=0,>0
{ 
   if(m<0)
	   return -1;
   else if(m==0)
	   return 0;
   else
	   return 1;
}