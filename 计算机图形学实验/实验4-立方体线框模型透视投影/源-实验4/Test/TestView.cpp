
// TestView.cpp : CTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//包含数学头文件
#define  PI 3.1415926//PI的宏定义
#define Round(d) int(floor(d+0.5))//四舍五入宏定义

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
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

// CTestView 构造/析构

CTestView::CTestView()
{
	// TODO: 在此处添加构造代码
	bPlay=FALSE;
	R=1000.0;d=900.0;Phi=90.0;Theta=0.0;
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘制

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	DoubleBuffer(pDC);
}


// CTestView 打印

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序


void CTestView::ReadPoint()//点表
{
	//顶点的三维坐标(x,y,z),立方体边长为2a
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

void CTestView::ReadFace()//面表
{
	//面的顶点数和面的顶点索引
	F[0].SetNum(4);F[0].vI[0]=4;F[0].vI[1]=5;F[0].vI[2]=6;F[0].vI[3]=7;//前面
	F[1].SetNum(4);F[1].vI[0]=0;F[1].vI[1]=3;F[1].vI[2]=2;F[1].vI[3]=1;//后面
	F[2].SetNum(4);F[2].vI[0]=0;F[2].vI[1]=4;F[2].vI[2]=7;F[2].vI[3]=3;//左面
	F[3].SetNum(4);F[3].vI[0]=1;F[3].vI[1]=2;F[3].vI[2]=6;F[3].vI[3]=5;//右面
	F[4].SetNum(4);F[4].vI[0]=2;F[4].vI[1]=3;F[4].vI[2]=7;F[4].vI[3]=6;//顶面
	F[5].SetNum(4);F[5].vI[0]=0;F[5].vI[1]=1;F[5].vI[2]=5;F[5].vI[3]=4;//底面
}

void CTestView::InitParameter()//透视变换参数初始化
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
	ViewPoint.x=R*k[5];//用户坐标系的视点球坐标
	ViewPoint.y=R*k[6];
	ViewPoint.z=R*k[4];
}

void CTestView::PerProject(CP3 P)//透视变换
{
	CP3 ViewP;
	// TODO
	ViewP.x=-k[1]*P.x+k[3]*P.y;//观察坐标系三维坐标
	ViewP.y=-k[7]*P.x-k[8]*P.y+k[2]*P.z;
	ViewP.z=-k[5]*P.x-k[6]*P.y-k[4]*P.z+R;
	ViewP.c=P.c;
	ScreenP.x=ROUND(d*ViewP.x/ViewP.z);//屏幕坐标系二维坐标
	ScreenP.y=ROUND(d*ViewP.y/ViewP.z);
	ScreenP.c=ViewP.c;
}

void CTestView::DoubleBuffer(CDC *pDC)//双缓冲
{
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(),rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//客户区中心为原点
	CDC memDC;//内存DC
	CBitmap NewBitmap,*pOldBitmap;//内存中承载的临时位图
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容位图
	pOldBitmap=memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	DrawObject(&memDC);//向memDC绘制图形
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图S
}

void CTestView::DrawObject(CDC* pDC)//绘制立方体线框
{
	CP2 t;
	CLine *line=new CLine;
	// TODO
	for(int nFace=0;nFace<6;nFace++)
	{
		for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//边循环
		{
			PerProject(P[F[nFace].p[nEdge]]);//透视投影
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
		line.LineTo(pDC,t.x,t.y,t.c);//闭合四边形
	}
	delete line;
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	R=R+100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}


//void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CView::OnLButtonUp(nFlags, point);
//}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi+=5;//设定步长
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
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SetWindowText(CString("案例19：立方体透视投影算法"));
	bPlay=bPlay?FALSE:TRUE;
	if (bPlay)//设置定时器
		SetTimer(1,150,NULL);
	else
		KillTimer(1);

}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Phi-=5;//设定步长
	Theta-=5;
	InitParameter();
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestView::OnUpdatePlay(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
		if(bPlay)
	{
		pCmdUI->SetCheck(TRUE);
		pCmdUI->SetText(CString("停止"));
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->SetText(CString("开始"));
	}
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	//return CView::OnEraseBkgnd(pDC);
}


void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	ReadPoint();
	ReadFace();
	InitParameter();
}


void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	R=R-100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}


void CTestView::OnOnepoint()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SetWindowText(CString("案例19：一点透视"));
	KillTimer(1);
	bPlay=FALSE;
	Phi=90;Theta=0;
	InitParameter();
	Invalidate(FALSE);
}


void CTestView::OnTwopoint()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SetWindowText(CString("案例19：二点透视"));
	KillTimer(1);
	bPlay=FALSE;
	Phi=90;Theta=30;
	InitParameter();
	Invalidate(FALSE);
}


void CTestView::OnThreepoint()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SetWindowText(CString("案例19：三点透视"));
	KillTimer(1);
	bPlay=FALSE;
	Theta=45;Phi=45;
	InitParameter();
	Invalidate(FALSE);
}
