// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
#define AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"

class CVector  
{
public:
	CVector();	
	virtual ~CVector();
	CVector(double,double,double);
	CVector(const CP3 &);
	CVector(const CP3 &,const CP3 &);
	double Mag();//ʸ����ģ
	CVector Normalize();//��λʸ��
	friend CVector operator +(const CVector &,const CVector &);//���������
	friend CVector operator -(const CVector &,const CVector &);
	friend CVector operator *(const CVector &,double);
	friend CVector operator *(double,const CVector &);
	friend CVector operator /(const CVector &,double);
	friend CVector operator+=(CVector &,CVector &);
	friend CVector operator-=(CVector &,CVector &);
	friend CVector operator*=(CVector &,CVector &);
	friend CVector operator/=(CVector &,double);
	friend double  Dot(const CVector &,const CVector &);  //ʸ�����
	friend CVector Cross(const CVector &,const CVector &);//ʸ�����
public:
	double x,y,z;//�������ݳ�Ա�������ⲿ����
};

#endif // !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
