// Face.cpp: implementation of the CFace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Face.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFace::CFace()
{
	vI=NULL;
	fNormal=CVector(CP3(0.0,0.0,1.0));
}

CFace::~CFace()
{
	if(vI!=NULL)
	{
		delete []vI;
		vI=NULL;
	}
}

void CFace::SetNum(int n)
{
	vN=n;
	vI=new int[n];
}

void CFace::SetFaceNormal(CP3 pt0,CP3 pt1,CP3 pt2)//计算小面法矢量
{
	CVector V01(pt0,pt1);
	CVector V02(pt0,pt2);
	fNormal=Cross(V01,V02);
}