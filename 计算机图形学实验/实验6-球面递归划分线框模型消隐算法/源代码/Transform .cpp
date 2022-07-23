// Transform.cpp: implementation of the CTransForm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Transform.h"
#include "math.h"
#define PI 3.14159
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

void CTransform::SetMat(CP3 *p,int n)
{
	POld=p;
	num=n;
}

void CTransform::Identity()//单位矩阵
{
	T[0][0]=1.0;T[0][1]=0.0;T[0][2]=0.0;T[0][3]=0.0;
	T[1][0]=0.0;T[1][1]=1.0;T[1][2]=0.0;T[1][3]=0.0;
	T[2][0]=0.0;T[2][1]=0.0;T[2][2]=1.0;T[2][3]=0.0;
	T[3][0]=0.0;T[3][1]=0.0;T[3][2]=0.0;T[3][3]=1.0;
}

void CTransform::Translate(double tx,double ty,double tz)//平移变换矩阵
{
	Identity();
	T[3][0]=tx; 
	T[3][1]=ty; 
	T[3][2]=tz; 
	MultiMatrix();
}

void CTransform::Scale(double sx,double sy,double sz)//比例变换矩阵
{
	Identity();
	T[0][0]=sx; 
	T[1][1]=sy; 
	T[2][2]=sz; 
	MultiMatrix();
}

void CTransform::Scale(double sx,double sy,double sz,CP3 p)//相对于任意点的比例变换矩阵
{
	Translate(-p.x,-p.y,-p.z);
	Scale(sx,sy,sz);
	Translate(p.x,p.y,p.z);
}

void CTransform::RotateX(double beta)//绕X轴旋转变换矩阵
{
	Identity();
	double rad=beta*PI/180;
	T[1][1]=cos(rad); T[1][2]=sin(rad);
	T[2][1]=-sin(rad);T[2][2]=cos(rad);
	MultiMatrix();
}

void CTransform::RotateX(double beta,CP3 p)//相对于任意点的绕X轴旋转变换矩阵
{
	Translate(-p.x,-p.y,-p.z);
	RotateX(beta);
	Translate(p.x,p.y,p.z);
}

void CTransform::RotateY(double beta)//绕Y轴旋转变换矩阵
{
	Identity();
	double rad=beta*PI/180;
	T[0][0]=cos(rad);T[0][2]=-sin(rad);
	T[2][0]=sin(rad);T[2][2]=cos(rad);
	MultiMatrix();
}

void CTransform::RotateY(double beta,CP3 p)//相对于任意点的绕Y轴旋转变换矩阵
{
	Translate(-p.x,-p.y,-p.z);
	RotateY(beta);
	Translate(p.x,p.y,p.z);
}

void CTransform::RotateZ(double beta)//绕Z轴旋转变换矩阵
{
	Identity();
	double rad=beta*PI/180;
	T[0][0]=cos(rad); T[0][1]=sin(rad);
	T[1][0]=-sin(rad);T[1][1]=cos(rad);
	MultiMatrix();
}

void CTransform::RotateZ(double beta,CP3 p)//相对于任意点的绕Z轴旋转变换矩阵
{
	Translate(-p.x,-p.y,-p.z);
	RotateZ(beta);
	Translate(p.x,p.y,p.z);
}

void CTransform::ReflectX()//X轴反射变换矩阵
{
	Identity();
	T[1][1]=-1;
	T[2][2]=-1;
	MultiMatrix();
}

void CTransform::ReflectY()//Y轴反射变换矩阵
{
	Identity();
	T[0][0]=-1;
	T[2][2]=-1;
	MultiMatrix();
}

void CTransform::ReflectZ()//Z轴反射变换矩阵
{
	Identity();
	T[0][0]=-1;
	T[1][1]=-1;
	MultiMatrix();
}

void CTransform::ReflectXOY()//XOY面反射变换矩阵
{
	Identity();
	T[2][2]=-1;
	MultiMatrix();
}

void CTransform::ReflectYOZ()//YOZ面反射变换矩阵
{
	Identity();
	T[0][0]=-1;
	MultiMatrix();
}

void CTransform::ReflectZOX()//ZOX面反射变换矩阵
{
	Identity();
	T[1][1]=-1;
	MultiMatrix();
}

void CTransform::ShearX(double d,double g)//X方向错切变换矩阵
{
	Identity();
	T[1][0]=d;
	T[2][0]=g;
	MultiMatrix();
}

void CTransform::ShearY(double b,double h)//Y方向错切变换矩阵
{
	Identity();
	T[0][1]=b;
	T[2][1]=h;
	MultiMatrix();
}

void CTransform::ShearZ(double c,double f)//Z方向错切变换矩阵
{
	Identity();
	T[0][2]=c;
	T[1][2]=f;
	MultiMatrix();
}
void CTransform::MultiMatrix()//矩阵相乘
{
	CP3 *PNew=new CP3[num];	
	for(int i=0;i<num;i++)
	{
		PNew[i]=POld[i];
	}
	for(int j=0;j<num;j++)
	{
		POld[j].x=PNew[j].x*T[0][0]+PNew[j].y*T[1][0]+PNew[j].z*T[2][0]+PNew[j].w*T[3][0];
		POld[j].y=PNew[j].x*T[0][1]+PNew[j].y*T[1][1]+PNew[j].z*T[2][1]+PNew[j].w*T[3][1];
		POld[j].z=PNew[j].x*T[0][2]+PNew[j].y*T[1][2]+PNew[j].z*T[2][2]+PNew[j].w*T[3][2];
		POld[j].w=PNew[j].x*T[0][3]+PNew[j].y*T[1][3]+PNew[j].z*T[2][3]+PNew[j].w*T[3][3];
	}
	delete []PNew;
}
