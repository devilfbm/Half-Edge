
// Half-EdgeView.cpp : CHalfEdgeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Half-Edge.h"
#endif

#include "Half-EdgeDoc.h"
#include "Half-EdgeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHalfEdgeView

IMPLEMENT_DYNCREATE(CHalfEdgeView, CView)

BEGIN_MESSAGE_MAP(CHalfEdgeView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CHalfEdgeView 构造/析构

CHalfEdgeView::CHalfEdgeView()
{
	// TODO:  在此处添加构造代码

}

CHalfEdgeView::~CHalfEdgeView()
{
}

BOOL CHalfEdgeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	// Frame 0: OpenGL必须使用以下标记
	//		WS_CLIPCHILDREN：裁减子窗口
	//						 当在父窗口绘制的时候，父窗口上还有一个子窗口的话，子窗口区域父窗口就不负责绘制。
	//		WS_CLIPSIBLINGS：裁剪兄弟窗口
	//							所有的overlapped和popup风格的窗口，都有WS_CLIPSIBLINGS 属性。
	//							也就是说这类风格的窗口，你是去不掉WS_CLIPSIBLINGS 属性的，不会在它重叠的兄弟窗口绘图；
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CHalfEdgeView 绘制

void CHalfEdgeView::OnDraw(CDC* /*pDC*/)
{
	CHalfEdgeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CHalfEdgeView 诊断

#ifdef _DEBUG
void CHalfEdgeView::AssertValid() const
{
	CView::AssertValid();
}

void CHalfEdgeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHalfEdgeDoc* CHalfEdgeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHalfEdgeDoc)));
	return (CHalfEdgeDoc*)m_pDocument;
}
#endif //_DEBUG


// CHalfEdgeView 消息处理程序


int CHalfEdgeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//Frame 2:加入初始化方法
	myInit();
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CHalfEdgeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


void CHalfEdgeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


BOOL CHalfEdgeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CView::OnEraseBkgnd(pDC);
}
