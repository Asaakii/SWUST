// Bucket.h: interface for the Bucket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUCKET_H__A2F5FA20_BB33_4949_8C03_F82DE5D8454B__INCLUDED_)
#define AFX_BUCKET_H__A2F5FA20_BB33_4949_8C03_F82DE5D8454B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AET.h"//包含AET表的头文件
class Bucket  
{
public:
	Bucket();
	virtual ~Bucket();
	int ScanLine;
	AET *p;//桶上的边表指针
	Bucket *next;
};

#endif // !defined(AFX_BUCKET_H__A2F5FA20_BB33_4949_8C03_F82DE5D8454B__INCLUDED_)
