// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define PI 3.1415926//Բ����
#include "math.h"//��ѧͷ�ļ�
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDM_PLAY, OnPlay)
	ON_UPDATE_COMMAND_UI(IDM_PLAY, OnUpdatePlay)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	bPlay=FALSE;
	R=800.0;d=1000.0;Phi=90.0;Theta=0.0;	
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	
	DoubleBuffer(pDC);	
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::ReadVertex()//���
{
	const double Golden_Section=(sqrt(5.0)-1.0)/2.0;//�ƽ�ָ����
	double a=160;//�ƽ���γ��ߵı߳�
	double b=a*Golden_Section;//�ƽ���ζ̱ߵı߳�
	Radius=sqrt(a*a+b*b);//����ʮ�����������뾶
	//�������ά����(x,y,z)
	V[0].x=0;  V[0].y=a;  V[0].z=b;  
	V[1].x=0;  V[1].y=a;  V[1].z=-b;
	V[2].x=a;  V[2].y=b;  V[2].z=0;
	V[3].x=a;  V[3].y=-b; V[3].z=0;
	V[4].x=0;  V[4].y=-a; V[4].z=-b;
	V[5].x=0;  V[5].y=-a; V[5].z=b;		
	V[6].x=b;  V[6].y=0;  V[6].z=a;  
	V[7].x=-b; V[7].y=0;  V[7].z=a;
	V[8].x=b;  V[8].y=0;  V[8].z=-a;
	V[9].x=-b; V[9].y=0;  V[9].z=-a;
	V[10].x=-a;V[10].y=b; V[10].z=0;
	V[11].x=-a;V[11].y=-b;V[11].z=0;
}

void CTestView::ReadFace()//���
{
	//��Ķ���������Ķ�������
	F[0].SetNum(3); F[0].vI[0]=0; F[0].vI[1]=6;  F[0].vI[2]=2;
	F[1].SetNum(3); F[1].vI[0]=2; F[1].vI[1]=6;  F[1].vI[2]=3;
	F[2].SetNum(3); F[2].vI[0]=3; F[2].vI[1]=6;  F[2].vI[2]=5;
	F[3].SetNum(3); F[3].vI[0]=5; F[3].vI[1]=6;  F[3].vI[2]=7;
	F[4].SetNum(3); F[4].vI[0]=0; F[4].vI[1]=7;  F[4].vI[2]=6;
	F[5].SetNum(3); F[5].vI[0]=2; F[5].vI[1]=3;  F[5].vI[2]=8;
	F[6].SetNum(3); F[6].vI[0]=1; F[6].vI[1]=2;  F[6].vI[2]=8;
	F[7].SetNum(3); F[7].vI[0]=0; F[7].vI[1]=2;  F[7].vI[2]=1;
	F[8].SetNum(3); F[8].vI[0]=0; F[8].vI[1]=1;  F[8].vI[2]=10;
	F[9].SetNum(3); F[9].vI[0]=1; F[9].vI[1]=9;  F[9].vI[2]=10;
	F[10].SetNum(3);F[10].vI[0]=1;F[10].vI[1]=8; F[10].vI[2]=9;
	F[11].SetNum(3);F[11].vI[0]=3;F[11].vI[1]=4; F[11].vI[2]=8;
	F[12].SetNum(3);F[12].vI[0]=3;F[12].vI[1]=5; F[12].vI[2]=4;
	F[13].SetNum(3);F[13].vI[0]=4;F[13].vI[1]=5; F[13].vI[2]=11;
	F[14].SetNum(3);F[14].vI[0]=7;F[14].vI[1]=10;F[14].vI[2]=11;
	F[15].SetNum(3);F[15].vI[0]=0;F[15].vI[1]=10;F[15].vI[2]=7;
	F[16].SetNum(3);F[16].vI[0]=4;F[16].vI[1]=11;F[16].vI[2]=9;
	F[17].SetNum(3);F[17].vI[0]=4;F[17].vI[1]=9; F[17].vI[2]=8;
	F[18].SetNum(3);F[18].vI[0]=5;F[18].vI[1]=7; F[18].vI[2]=11;
	F[19].SetNum(3);F[19].vI[0]=9;F[19].vI[1]=11;F[19].vI[2]=10;
}

void CTestView::InitParameter()//͸�ӱ任������ʼ��
{	
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}

void CTestView::PerProject(CP3 P)//͸�ӱ任
{
	CP3 ViewP;
	ViewP.x=P.x*k[3]-P.z*k[1];//�۲�����ϵ��ά����
	ViewP.y=-P.x*k[8]+P.y*k[2]-P.z*k[7];
	ViewP.z=-P.x*k[6]-P.y*k[4]-P.z*k[5]+R;
	ScreenP.x=d*ViewP.x/ViewP.z;//��Ļ����ϵ��ά����
	ScreenP.y=d*ViewP.y/ViewP.z;
}

void CTestView::DoubleBuffer(CDC* pDC)//˫����
{
	CRect rect;//����ͻ�������
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������Χ,x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//�ͻ�������Ϊԭ��
	CDC memDC;//�ڴ�DC
	memDC.CreateCompatibleDC(pDC);//����һ������ʾpDC���ݵ��ڴ�memDC
	CBitmap NewBitmap,*pOldBitmap;//�ڴ��г��ص���ʱλͼ 
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
	NewBitmap.DeleteObject();//ɾ��λͼ
}

void CTestView::DrawObject(CDC* pDC)//��������
{
	int n=3;//�ݹ����
	for(int nFace=0;nFace<20;nFace++)//��ѭ��
	{
		CP3 Point[3];//͸��ͶӰ�������ά��������
		for(int nVertex=0;nVertex<F[nFace].vN;nVertex++)//����ѭ��
		{
			Point[nVertex]=V[F[nFace].vI[nVertex]];	
		}
		SubDivide(pDC,Point[0],Point[1],Point[2],n);		
	}
}

void CTestView::SubDivide(CDC *pDC,CP3 p0, CP3 p1, CP3 p2,int n)//�ݹ麯��
{
	if(0==n)
	{
		DrawTriangle(pDC,p0,p1,p2);
		return;
	}
	else
	{
		CP3 p01,p12,p20;
		p01=(p0+p1)/2.0;
		p12=(p1+p2)/2.0;
		p20=(p2+p0)/2.0;	
		Normalize(p01);//��չģ��
		Normalize(p12);
		Normalize(p20);
		SubDivide(pDC,p0,p01,p20,n-1);//�ݹ����
		SubDivide(pDC,p1,p12,p01,n-1);
		SubDivide(pDC,p2,p20,p12,n-1);
		SubDivide(pDC,p01,p12,p20,n-1);
	}
}

void CTestView::Normalize(CP3 &p)
{
	if(0==p.Mag())
		return;
	p/=p.Mag();//ģ����λ��
	p*=Radius;//��չ��������
}

void CTestView::DrawTriangle(CDC *pDC,CP3 p0, CP3 p1, CP3 p2)
{
	CLine *line=new CLine;
	//���޳�����Ȼ��͸�ӱ任
	CP3 point[3];
	CVector ViewVector(p0,ViewPoint);//�����ʸ��
	ViewVector=ViewVector.Normalize();//��λ����ʸ��
	CVector V01(p0,p1);//���һ����ʸ��
	CVector V02(p0,p2);//�����һ����ʸ��		
	CVector FNormal=Cross(V01,V02);//��ķ�ʸ��	
	FNormal.Normalize();//��λ����ʸ��
	if(Dot(ViewVector,FNormal)>=0)//�����޳�
	{
		PerProject(p0);//͸��ͶӰp0
		point[0]=ScreenP;
		PerProject(p1);//͸��ͶӰp1
		point[1]=ScreenP;
		PerProject(p2); //͸��ͶӰp2
		point[2]=ScreenP;
		line->MoveTo(pDC,point[0].x,point[0].y);
		line->LineTo(pDC,point[1].x,point[1].y);
		line->LineTo(pDC,point[2].x,point[2].y);
		line->LineTo(pDC,point[0].x,point[0].y);	
	}
	delete line;
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//����������
{
	// TODO: Add your message handler code here and/or call default
	R=R+100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnRButtonDblClk(UINT nFlags, CPoint point)//����Ҽ����� 
{
	// TODO: Add your message handler code here and/or call default
	R=R-100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnRButtonDblClk(nFlags, point);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Alpha=-5;
			tran.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha=5;
			tran.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta=-5;
			tran.RotateY(Beta);
			break;
		case VK_RIGHT:
		    Beta=5;
			tran.RotateY(Beta);
			break;
		default:
			break;			
		}
		Invalidate(FALSE);	
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnPlay() 
{
	// TODO: Add your command handler code here
	bPlay=bPlay?FALSE:TRUE;
	if(bPlay)//���ö�ʱ��
		SetTimer(1,150,NULL);	
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent)//����ʱ�亯�� 
{
	// TODO: Add your message handler code here and/or call default
	Alpha=5;Beta=5;
	tran.RotateX(Alpha);
	tran.RotateY(Beta);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(bPlay)
	{
		pCmdUI->SetCheck(TRUE);
		pCmdUI->SetText("ֹͣ");
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->SetText("��ʼ");
	}
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC)//��ֹ����ˢ�� 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	ReadVertex();
	ReadFace();
	tran.SetMat(V,12);
	InitParameter();
}




