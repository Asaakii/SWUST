// Edge.h: interface for the Edge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGE_H__7A2836FC_0998_48C2_9107_57134BD7E4B1__INCLUDED_)
#define AFX_EDGE_H__7A2836FC_0998_48C2_9107_57134BD7E4B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Edge  
{
public:
	Edge();
	virtual ~Edge();
	double x;
	int yMax;
	double k;//´úÌæ1/k
	Edge *next;
};

#endif // !defined(AFX_EDGE_H__7A2836FC_0998_48C2_9107_57134BD7E4B1__INCLUDED_)
