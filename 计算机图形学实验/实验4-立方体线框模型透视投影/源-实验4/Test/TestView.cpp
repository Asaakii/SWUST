
// TestView.cpp : CTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//������ѧͷ�ļ�
#define  PI 3.1415926//PI�ĺ궨��
#define Round(d) int(floor(d+0.5))//��������궨��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(IDM_DRAWPIC, &CTestView::OnDrawpic)
	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDM_PLAY, &CTestView::OnPlay)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(IDM_PLAY, &CTestView::OnUpdatePlay)
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ONEPOINT, &CTestView::OnOnepoint)
	ON_COMMAND(ID_TWOPOINT, &CTestView::OnTwopoint)
	ON_COMMAND(ID_THREEPOINT, &CTestView::OnThreepoint)
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������
	bPlay=FALSE;
	R=1000.0;d=900.0;Phi=90.0;Theta=0.0;
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestView ����

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	DoubleBuffer(pDC);
}


// CTestView ��ӡ

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CTestView ���

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView ��Ϣ�������


void CTestView::ReadPoint()//���
{
	//�������ά����(x,y,z),������߳�Ϊ2a
	double a=150;
	P[0].x=-a;P[0].y=-a;P[0].z=-a;
	P[1].x=+a;P[1].y=-a;P[1].z=-a;
	P[2].x=+a;P[2].y=+a;P[2].z=-a;
	P[3].x=-a;P[3].y=+a;P[3].z=-a;
	P[4].x=-a;P[4].y=-a;P[4].z=+a;
	P[5].x=+a;P[5].y=-a;P[5].z=+a;
	P[6].x=+a;P[6].y=+a;P[6].z=+a;
	P[7].x=-a;P[7].y=+a;P[7].z=+a;
}

void CTestView::ReadFace()//���
{
	//��Ķ���������Ķ�������
	F[0].SetNum(4);F[0].vI[0]=4;F[0].vI[1]=5;F[0].vI[2]=6;F[0].vI[3]=7;//ǰ��
	F[1].SetNum(4);F[1].vI[0]=0;F[1].vI[1]=3;F[1].vI[2]=2;F[1].vI[3]=1;//����
	F[2].SetNum(4);F[2].vI[0]=0;F[2].vI[1]=4;F[2].vI[2]=7;F[2].vI[3]=3;//����
	F[3].SetNum(4);F[3].vI[0]=1;F[3].vI[1]=2;F[3].vI[2]=6;F[3].vI[3]=5;//����
	F[4].SetNum(4);F[4].vI[0]=2;F[4].vI[1]=3;F[4].vI[2]=7;F[4].vI[3]=6;//����
	F[5].SetNum(4);F[5].vI[0]=0;F[5].vI[1]=1;F[5].vI[2]=5;F[5].vI[3]=4;//����
}

void CTestView::InitParameter()//͸�ӱ任������ʼ��
{
	// TODO
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[3]*k[2];
	k[6]=k[1]*k[2];
	k[7]=k[3]*k[4];
	k[8]=k[1]*k[4];
	ViewPoint.x=R*k[5];//�û�����ϵ���ӵ�������
	ViewPoint.y=R*k[6];
	ViewPoint.z=R*k[4];
}

void CTestView::PerProject(CP3 P)//͸�ӱ任
{
	CP3 ViewP;
	// TODO
	ViewP.x=-k[1]*P.x+k[3]*P.y;//�۲�����ϵ��ά����
	ViewP.y=-k[7]*P.x-k[8]*P.y+k[2]*P.z;
	ViewP.z=-k[5]*P.x-k[6]*P.y-k[4]*P.z+R;
	ViewP.c=P.c;
	ScreenP.x=ROUND(d*ViewP.x/ViewP.z);//��Ļ����ϵ��ά����
	ScreenP.y=ROUND(d*ViewP.y/ViewP.z);
	ScreenP.c=ViewP.c;
}

void CTestView::DoubleBuffer(CDC *pDC)//˫����
{
	CRect rect;//����ͻ�������
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������Χ,x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//�ͻ�������Ϊԭ��
	CDC memDC;//�ڴ�DC
	CBitmap NewBitmap,*pOldBitmap;//�ڴ��г��ص���ʱλͼ
	memDC.CreateCompatibleDC(pDC);//����һ������ʾpDC���ݵ��ڴ�memDC
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//��������λͼ
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ��memDC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//��ԭ���������ͻ����������Ǻ�ɫ
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	DrawObject(&memDC);//��memDC����ͼ��
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼS
}

void CTestView::DrawObject(CDC* pDC)//�����������߿�
{
	CP2 t;
	CLine *line=new CLine;
	// TODO
	for(int nFace=0;nFace<6;nFace++)
	{
		for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//��ѭ��
		{
			PerProject(P[F[nFace].p[nEdge]]);//͸��ͶӰ
			if(nEdge==0)
			{
				line.MoveTo(pDC,ScreenP);
				t=ScreenP;
			}
			else
			{
				line.LineTo(pDC,ScreenP);
			}		
		}
		line.LineTo(pDC,t.x,t.y,t.c);//�պ��ı���
	}
	delete line;
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	R=R+100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}


//void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CView::OnLButtonUp(nFlags, point);
//}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi+=5;//�趨����
			break;
		case VK_DOWN:
			Phi-=5;
			break;
		case VK_LEFT:
			Theta+=5;
			break;
		case VK_RIGHT:
		    Theta-=5;
			break;
		default:
			break;
		}
		InitParameter();
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTestView::OnPlay()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->SetWindowText(CString("����19��������͸��ͶӰ�㷨"));
	bPlay=bPlay?FALSE:TRUE;
	if (bPlay)//���ö�ʱ��
		SetTimer(1,150,NULL);
	else
		KillTimer(1);

}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Phi-=5;//�趨����
	Theta-=5;
	InitParameter();
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestView::OnUpdatePlay(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		if(bPlay)
	{
		pCmdUI->SetCheck(TRUE);
		pCmdUI->SetText(CString("ֹͣ"));
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->SetText(CString("��ʼ"));
	}
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return true;
	//return CView::OnEraseBkgnd(pDC);
}


void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	ReadPoint();
	ReadFace();
	InitParameter();
}


void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	R=R-100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}


void CTestView::OnOnepoint()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->SetWindowText(CString("����19��һ��͸��"));
	KillTimer(1);
	bPlay=FALSE;
	Phi=90;Theta=0;
	InitParameter();
	Invalidate(FALSE);
}


void CTestView::OnTwopoint()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->SetWindowText(CString("����19������͸��"));
	KillTimer(1);
	bPlay=FALSE;
	Phi=90;Theta=30;
	InitParameter();
	Invalidate(FALSE);
}


void CTestView::OnThreepoint()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->SetWindowText(CString("����19������͸��"));
	KillTimer(1);
	bPlay=FALSE;
	Theta=45;Phi=45;
	InitParameter();
	Invalidate(FALSE);
}
