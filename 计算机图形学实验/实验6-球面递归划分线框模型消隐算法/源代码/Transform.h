// Transform.h: interface for the CTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_)
#define AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"

class CTransform//三维变换  
{
public:
	CTransform();
	virtual ~CTransform();
	void SetMat(CP3 *,int);
	void Identity();
	void Translate(double,double,double);//平移变换矩阵
	void Scale(double,double,double);//比例变换矩阵
	void Scale(double,double,double,CP3);//相对于任意点的比例变换矩阵
	void RotateX(double);//旋转变换矩阵
	void RotateX(double,CP3);//相对于任意点的X旋转变换矩阵
	void RotateY(double);//旋转变换矩阵
	void RotateY(double,CP3);//相对于任意点的Y旋转变换矩阵
	void RotateZ(double);//旋转变换矩阵
	void RotateZ(double,CP3);//相对于任意点的Z旋转变换矩阵
	void ReflectX();//X轴反射变换矩阵
	void ReflectY();//Y轴反射变换矩阵
	void ReflectZ();//Z轴反射变换矩阵
	void ReflectXOY();//XOY面反射变换矩阵
	void ReflectYOZ();//YOZ面反射变换矩阵
	void ReflectZOX();//ZOX面反射变换矩阵
	void ShearX(double,double);//X方向错切变换矩阵
	void ShearY(double,double);//Y方向错切变换矩阵
	void ShearZ(double,double);//Z方向错切变换矩阵
	void MultiMatrix();//矩阵相乘
public:
	double T[4][4];
	CP3 *POld;
	int num;
};
#endif // !defined(AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_)
