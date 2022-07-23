// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"

#include "Line.h" 
#include "math.h" 
#define Round(d) int(floor(d+0.5))											//��������궨��
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

void CLine::MoveTo(CDC *pDC,CP2 p0)											//����ֱ����㺯��
{
	P0=p0;
}

void CLine::MoveTo(CDC *pDC,double x0,double y0)							//���غ���
{
	P0=CP2(x0,y0);
}

void CLine::LineTo(CDC *pDC,CP2 p1)
{
	P1=p1;
	CP2 p,t;
	COLORREF clr=RGB(0.0,0.0,0.0);											//��ɫ���ص�
	if(fabs(P0.x-P1.x)<1e-6)												//���ƴ���
	{
		if(P0.y>P1.y)														//��������,ʹ����ʼ������յ�
		{
			t=P0;P0=P1;P1=t;
		}
		for(p=P0;p.y<P1.y;p.y++)
		{
			pDC->SetPixelV(Round(p.x),Round(p.y),clr);
		}
	}
	else
	{ 
		double k,d; 
		k=(P1.y-P0.y)/(P1.x-P0.x);											//б��
		if(k>1.0)															//����k>1��yΪ������
		{
			if(P0.y>P1.y)
			{
				t=P0;P0=P1;P1=t;
			}
			d=1-0.5*k;														//�е��ʼֵ
			for(p=P0;p.y<P1.y;p.y++)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d>=0)													//�е�λ�ڽ����Ƶ��Ϸ�������·���
				{
					p.x++;
					d+=1-k;													//���ƹ�ʽ:��d>=0ʱ��d(i+1)=d(i)+1-k;
				}
				else
					d+=1;
			}
		}
		if(0.0<=k && k<=1.0)												//����0<=k<=1��xΪ������
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}
			d=0.5-k;														//�е��ʼֵ
			for(p=P0;p.x<P1.x;p.x++)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d<0)														//�е�λ�ڽ����Ƶ��·�������Ϸ���
				{
					p.y++;
					d+=1-k;													//���ƹ�ʽ:��d<0ʱ��d(i+1)=d(i)+1-k;
				}
				else
					d-=k;
			}
		}
		if(k>=-1.0 && k<0.0)												//����-1<=k<0��xΪ������
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}
			d=-0.5-k;														//�е��ʼ��
			for(p=P0;p.x<P1.x;p.x++)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d>0)														//�е�λ�ڽ����Ƶ��Ϸ�������·���
				{
					p.y--;
					d-=1+k;													//���ƹ�ʽ:��d>0ʱ��d(i+1)=d(i)-1-k;
				}
				else
					d-=k;
			}
		}
		if(k<-1.0)															//����k<-1 ��yΪ������
		{
			if(P0.y<P1.y)
			{
				t=P0;P0=P1;P1=t;
			}
			d=-1-0.5*k;
			for(p=P0;p.y>P1.y;p.y--)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d<0)														//�е�λ�ڽ����Ƶ��·�������Ϸ���
				{
					p.x++;
					d-=1+k;													//���ƹ�ʽ:��d>0ʱ��d(i+1)=d(i)-1-k;
				}
				else
					d-=1;
			}
		}
	}
	P0=p1;																	//���յ㸳ֵ�����
}

void CLine::LineTo(CDC *pDC,double x1,double y1)							//���غ���
{
	LineTo(pDC,CP2(x1,y1));
}