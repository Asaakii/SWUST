// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ROUND(a) int(a+0.5)//��������
/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(ID_MENUAET, OnMenuAET)
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
	//���ö���ε�7������	
	Point[0]=CPoint(412,535);//P0
	Point[1]=CPoint(463,209);//P1
	Point[2]=CPoint(580,431);//P2
	Point[3]=CPoint(627,321);//P3
	Point[4]=CPoint(716,464);//P4
	Point[5]=CPoint(768,398);//P5
	Point[6]=CPoint(801,506);//P6
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
	pDC->Polygon(Point,7);//���ƶ����
	//�������εĶ�����
	pDC->TextOut(412,535,"P0");
	pDC->TextOut(463,209,"P1");
    pDC->TextOut(580,431,"P2");
	pDC->TextOut(627,321,"P3");
	pDC->TextOut(716,464,"P4");
	pDC->TextOut(768,398,"P5");
	pDC->TextOut(801,506,"P6");
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
void CTestView::OnMenuAET() //�˵�����
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("�������Ч�߱�����㷨");//��ʾ����
	
	CColorDialog ccd(GetColor);
	if(ccd.DoModal()==IDOK)//���õ�ɫ��ѡȡǰ��ɫ
	{
		GetColor=ccd.GetColor();
	}
	RedrawWindow();//ˢ����Ļ
	CreatBucket();//��ʼ��Ͱ
	Et();//���ڽ����߱�	
	PolygonFill();//��������	
}

void CTestView::CreatBucket()//����Ͱ���
{
	int ScanMin,ScanMax;//ȷ��ɨ���ߵ���Сֵ�����ֵ
	ScanMax=ScanMin=Point[0].y;
	for(int i=1;i<Number;i++)
	{
		if(Point[i].y<ScanMin)
		{
			ScanMin=Point[i].y;//ɨ���ߵ���Сֵ			
		}
		if(Point[i].y>ScanMax)
		{
			ScanMax=Point[i].y;//ɨ���ߵ����ֵ
		}
	}	
	for(i=ScanMin;i<=ScanMax;i++)//����Ͱ���
	{
		if(ScanMin==i)//Ͱͷ���
		{
			HeadB=new Bucket;//����Ͱ��ͷ���
			CurrentB=HeadB;//CurrentBΪBucket��ǰ���ָ��
			CurrentB->ScanLine=ScanMin;
			CurrentB->p=NULL;//û�����ӱ�����
			CurrentB->next=NULL;
		}
		else//����Ͱ���������
		{
			CurrentB->next=new Bucket;//�½�һ��Ͱ���
			CurrentB=CurrentB->next;//ʹCurrentBָ���½���Ͱ���
			CurrentB->ScanLine=i;
			CurrentB->p=NULL;//û�����ӱ�����
			CurrentB->next=NULL;				
		}
	}
}

void CTestView::Et()//����߱�
{
	for(int i=0;i<Number;i++)//����ÿ������
	{
		CurrentB=HeadB;//��Ͱ�����ͷ��㿪ʼѭ��
		int j=i+1;//�ߵĵڶ������㣬Point[i]��Point[j]���ɱ�
		if(j==Number) j=0;//��֤����εıպ�
		if(Point[j].y>Point[i].y)//�յ������
		{
			while(CurrentB->ScanLine!=Point[i].y)//��Ͱ��Ѱ�Ҹñߵ�yMin
			{
				CurrentB=CurrentB->next;//�Ƶ���һ��Ͱ���
			}
			E[i].x=Point[i].x;//����AET���ֵ
			E[i].yMax=Point[j].y;
			E[i].k=double((Point[j].x-Point[i].x))/(Point[j].y-Point[i].y);//����1/k			
			E[i].next=NULL;
			CurrentE=CurrentB->p;//���Ͱ�����ӱ߱�ĵ�ַ
			if(CurrentB->p==NULL)//��ǰͰ�����û�����ӱ߽��
			{
				CurrentE=&E[i];//���ߵ���ʼ��ַ
				CurrentB->p=CurrentE;//��һ���߽��ֱ�����ӵ���Ӧ��Ͱ��
			}
			else
			{
				while(CurrentE->next!=NULL)//�����ǰ�������б߽��
				{
					CurrentE=CurrentE->next;//�ƶ�ָ�뵽��ǰ�ߵ����һ���߽��					
				}
				CurrentE->next=&E[i];//�ѵ�ǰ�߽���ȥ
			}
		}
		if(Point[j].y<Point[i].y)//�յ������
		{
			while(CurrentB->ScanLine!=Point[j].y)
			{
				CurrentB=CurrentB->next;				
			}
			E[i].x=Point[j].x;
			E[i].yMax=Point[i].y;
			E[i].k=double((Point[i].x-Point[j].x))/(Point[i].y-Point[j].y);			
			E[i].next=NULL;
			CurrentE=CurrentB->p;
			if(CurrentE==NULL)
			{
				CurrentE=&E[i];
				CurrentB->p=CurrentE;
			}
			else
			{
				while(CurrentE->next!=NULL)
				{
					CurrentE=CurrentE->next;				
				}
				CurrentE->next=&E[i];
			}
		}
	}
	CurrentB=NULL;
	CurrentE=NULL;	
}

void CTestView::AddEdge(AET *NewEdge)//������ʱ�߱�
{
	T1=HeadE;
	if(T1==NULL)//�߱�Ϊ��,���߱���ΪTempEdge
	{
		T1=NewEdge;
		HeadE=T1;
	}
	else
	{
		while(T1->next!=NULL)//�߱�Ϊ��,��TempEdge���ڸñ�֮��
		{
			T1=T1->next;
		}
		T1->next=NewEdge;
	}
}

void CTestView::EdgeOrder()//�Ա߱��������
{	
	T1=HeadE;
	if(T1==NULL)
	{
		return;
	}
	if(T1->next==NULL)//����ñ߱�û�������߱�
	{
		return;//Ͱ���ֻ��һ���ߣ�����Ҫ����
	}
	else
	{
		if(T1->next->x<T1->x)//�߱�xֵ����
		{
			T2=T1->next;
			T1->next=T2->next;
			T2->next=T1;
			HeadE=T2;
		}
		T2=HeadE;
		T1=HeadE->next;		
		while(T1->next!=NULL)//���������Ƚ������ı߱��xֵ,��������
		{
			if(T1->next->x<T1->x)
			{
				T2->next=T1->next;
				T1->next=T1->next->next;
				T2->next->next=T1;
				T2=T2->next;
			}
			else
			{
				T2=T1;
				T1=T1->next;
			}
		}
	}
}

void CTestView::PolygonFill()//��������
{
	HeadE=NULL;
	for(CurrentB=HeadB;CurrentB!=NULL;CurrentB=CurrentB->next)//��������Ͱ���
	{
		for(CurrentE=CurrentB->p;CurrentE!=NULL;CurrentE=CurrentE->next)//����Ͱ������ǰ�ı߽��			
		{
			AET *TempEdge=new AET;
			TempEdge->x=CurrentE->x;
			TempEdge->yMax=CurrentE->yMax;
			TempEdge->k=CurrentE->k;
			TempEdge->next=NULL;			
			AddEdge(TempEdge);//���ñ߲�����ʱAet��
		}
		EdgeOrder();//ʹ�ñ߱���x������˳����		
		T1=HeadE;//����ymax����ɨ����ı߽��
		if(T1==NULL)
		{
			return;
		}
		while(CurrentB->ScanLine>=T1->yMax)//�����ý�㣬Aet��ָ����ƣ��±��Ͽ���
		{
			T1=T1->next;
			HeadE=T1;
			if(HeadE==NULL)
			{
				return;
			}
		}
		if(T1->next!=NULL)
		{
			T2=T1;
			T1=T2->next;
		}
		while(T1!=NULL)
		{
			if(CurrentB->ScanLine>=T1->yMax)//����һ�����
			{
				T2->next=T1->next;
				T1->next=NULL;
				T1=T2->next;
			}
			else
			{
				T2=T1;
				T1=T2->next;
			}
		}
		BOOL In=false;//����һ��BOOL����In����ʼֵΪ��
		double xb,xe;//ɨ���ߵ������յ�
		for(T1=HeadE;T1!=NULL;T1=T1->next)//���ɨ���ߺͶ�����ཻ������
		{
			if(In==false)
			{
				xb=T1->x;
				In=true;//ÿ����һ�����,��Inֵȡ��һ��
			}
			else//���InֵΪ�棬�����ӵ�ǰ����xֵ��ʼ����һ����xֵ����������
			{
				xe=T1->x-1;//����ҿ�
				CClientDC dc(this);
				for(double x=xb;x<=xe;x++)
					dc.SetPixel(ROUND(x),CurrentB->ScanLine,GetColor);//������
				Sleep(1);//��ʱ1ms,��������̵Ŀ�����
				In=FALSE;
			}		
		}
		for(T1=HeadE;T1!=NULL;T1=T1->next)//��������
		{
			T1->x=T1->x+T1->k;//x=x+1/k				 
		}				
	}
	delete HeadB; 
	delete CurrentB;
	delete CurrentE;
	delete HeadE;
}