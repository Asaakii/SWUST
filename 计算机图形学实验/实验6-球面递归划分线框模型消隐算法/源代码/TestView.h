// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Face.h"
#include "Vector.h"
#include "Line.h"
#include "Transform.h"

class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument();

// Operations
public:
	void ReadVertex();//���붥���
	void ReadFace();//�������
	void InitParameter();//������ʼ��
	void PerProject(CP3 P);//͸��ͶӰ
	void DoubleBuffer(CDC* pDC);//˫����
	void DrawObject(CDC* pDC);//��������
	void SubDivide(CDC *pDC,CP3 p0, CP3 p1, CP3 p2,int n);//�ݹ麯��
	void DrawTriangle(CDC *pDC,CP3 p0, CP3 p1, CP3 p2);//���������κ���
	void Normalize(CP3 &p);//ʸ����չ����
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 V[12];//���
	CFace F[20];//���
	double R,Theta,Phi,d;//R,Theta,Phi�ӵ����û�����ϵ��������,d�Ӿ�
	double k[9];//���㳣��
	CP3 ViewPoint;//�ӵ���άֱ������
	CP3 ScreenP;//͸����ά����
	BOOL bPlay;//��������
	double Radius;//����뾶
	double Alpha,Beta;//x������ת����,y������ת�½�
	CTransform tran;//�任����
	// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPlay();
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument()
   { return (CTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
