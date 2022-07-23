// AET.h: interface for the AET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AET_H__406FC882_620F_4465_82AD_6F6D129DFDFA__INCLUDED_)
#define AFX_AET_H__406FC882_620F_4465_82AD_6F6D129DFDFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AET  
{
public:
	AET();
	virtual ~AET();
	double x;
	int yMax;
	double k;//´úÌæ1/k
	AET *next;
};

#endif // !defined(AFX_AET_H__406FC882_620F_4465_82AD_6F6D129DFDFA__INCLUDED_)
