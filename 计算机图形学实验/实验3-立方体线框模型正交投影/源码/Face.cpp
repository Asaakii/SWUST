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
}

CFace::~CFace()
{
	if(vI!=NULL)
	{
		delete []vI;
		vI=NULL;
	}
}

void CFace::SetNum(int vN)
{
	this->vN=vN;
	vI=new int[vN];
}