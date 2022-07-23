// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"

#include "Line.h" 
#include "math.h" 
#define Round(d) int(floor(d+0.5))											//四舍五入宏定义
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

void CLine::MoveTo(CDC *pDC,CP2 p0)											//绘制直线起点函数
{
	P0=p0;
}

void CLine::MoveTo(CDC *pDC,double x0,double y0)							//重载函数
{
	P0=CP2(x0,y0);
}

void CLine::LineTo(CDC *pDC,CP2 p1)
{
	P1=p1;
	CP2 p,t;
	COLORREF clr=RGB(0.0,0.0,0.0);											//黑色像素点
	if(fabs(P0.x-P1.x)<1e-6)												//绘制垂线
	{
		if(P0.y>P1.y)														//交换顶点,使得起始点低于终点
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
		k=(P1.y-P0.y)/(P1.x-P0.x);											//斜率
		if(k>1.0)															//绘制k>1（y为主方向）
		{
			if(P0.y>P1.y)
			{
				t=P0;P0=P1;P1=t;
			}
			d=1-0.5*k;														//中点初始值
			for(p=P0;p.y<P1.y;p.y++)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d>=0)													//中点位于将绘制点上方，填充下方点
				{
					p.x++;
					d+=1-k;													//递推公式:当d>=0时，d(i+1)=d(i)+1-k;
				}
				else
					d+=1;
			}
		}
		if(0.0<=k && k<=1.0)												//绘制0<=k<=1（x为主方向）
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}
			d=0.5-k;														//中点初始值
			for(p=P0;p.x<P1.x;p.x++)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d<0)														//中点位于将绘制点下方，填充上方点
				{
					p.y++;
					d+=1-k;													//递推公式:当d<0时，d(i+1)=d(i)+1-k;
				}
				else
					d-=k;
			}
		}
		if(k>=-1.0 && k<0.0)												//绘制-1<=k<0（x为主方向）
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}
			d=-0.5-k;														//中点初始化
			for(p=P0;p.x<P1.x;p.x++)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d>0)														//中点位于将绘制点上方，填充下方点
				{
					p.y--;
					d-=1+k;													//递推公式:当d>0时，d(i+1)=d(i)-1-k;
				}
				else
					d-=k;
			}
		}
		if(k<-1.0)															//绘制k<-1 （y为主方向）
		{
			if(P0.y<P1.y)
			{
				t=P0;P0=P1;P1=t;
			}
			d=-1-0.5*k;
			for(p=P0;p.y>P1.y;p.y--)
			{
				pDC->SetPixelV(Round(p.x),Round(p.y),clr);
				if(d<0)														//中点位于将绘制点下方，填充上方点
				{
					p.x++;
					d-=1+k;													//递推公式:当d>0时，d(i+1)=d(i)-1-k;
				}
				else
					d-=1;
			}
		}
	}
	P0=p1;																	//将终点赋值给起点
}

void CLine::LineTo(CDC *pDC,double x1,double y1)							//重载函数
{
	LineTo(pDC,CP2(x1,y1));
}