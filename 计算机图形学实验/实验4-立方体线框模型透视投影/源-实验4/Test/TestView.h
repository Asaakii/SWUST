
// TestView.h : CTestView ��Ľӿ�
//

#pragma once

#include "Line.h"
#include "Face.h"
#include "P3.h"
class CTestView : public CView
{
protected: // �������л�����
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// ����
public:
	CTestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	void ReadPoint();//������
	void ReadFace();//�������
	void InitParameter();//������ʼ��
	void PerProject(CP3);//͸��ͶӰ
	void DoubleBuffer(CDC *pDC);//˫�����ͼ
	void DrawObject(CDC *);//�������������
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 P[8];//���
	CFace F[6];//���
	double R,Theta,Phi,d;//R,Theta,Phi�ӵ����û�����ϵ��������,d�Ӿ�
	double k[9];//���㳣��
	CP2 ScreenP;//��Ļ����ϵ�Ķ�ά�����
	BOOL bPlay;//��������
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDrawpic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPlay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdatePlay(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOnepoint();
	afx_msg void OnTwopoint();
	afx_msg void OnThreepoint();
};

#ifndef _DEBUG  // TestView.cpp �еĵ��԰汾
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

