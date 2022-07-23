// Transform.h: interface for the CTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_)
#define AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"

class CTransform//��ά�任  
{
public:
	CTransform();
	virtual ~CTransform();
	void SetMat(CP3 *,int);
	void Identity();
	void Translate(double,double,double);//ƽ�Ʊ任����
	void Scale(double,double,double);//�����任����
	void Scale(double,double,double,CP3);//����������ı����任����
	void RotateX(double);//��ת�任����
	void RotateX(double,CP3);//�����������X��ת�任����
	void RotateY(double);//��ת�任����
	void RotateY(double,CP3);//�����������Y��ת�任����
	void RotateZ(double);//��ת�任����
	void RotateZ(double,CP3);//�����������Z��ת�任����
	void ReflectX();//X�ᷴ��任����
	void ReflectY();//Y�ᷴ��任����
	void ReflectZ();//Z�ᷴ��任����
	void ReflectXOY();//XOY�淴��任����
	void ReflectYOZ();//YOZ�淴��任����
	void ReflectZOX();//ZOX�淴��任����
	void ShearX(double,double);//X������б任����
	void ShearY(double,double);//Y������б任����
	void ShearZ(double,double);//Z������б任����
	void MultiMatrix();//�������
public:
	double T[4][4];
	CP3 *POld;
	int num;
};
#endif // !defined(AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_)
