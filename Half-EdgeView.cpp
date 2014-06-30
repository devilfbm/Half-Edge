
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
// Frame 9:
//		设置标记
CHalfEdgeView::CHalfEdgeView()
{
	// TODO:  在此处添加构造代码
	m_bPoint = FALSE;
	m_bLine = FALSE;
	m_bPolygon = FALSE;
	m_bTriangle = FALSE;
	m_bCube = FALSE;
	m_bTorus = FALSE;
	m_bTeapot = FALSE;
	m_bIcosahedron = TRUE;
	m_bSimpleCube = FALSE;
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
// Frame 6:
void CHalfEdgeView::OnDraw(CDC* /*pDC*/)
{
	CHalfEdgeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	// 
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	// Flush
	::glFinish();
	// 交互
	::SwapBuffers(m_pDC->GetSafeHdc());
}

// Frame 10:
//		描绘物体的事件处理程序
// 茶壶
void CHalfEdgeView::OnObjectsTeapot()
{
	m_bCube = FALSE;
	m_bTorus = FALSE;
	m_bTeapot = TRUE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// 立方体
void CHalfEdgeView::OnObjectsCube()
{
	m_bCube = TRUE;
	m_bTorus = FALSE;
	m_bTeapot = FALSE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// 二十面体
void CHalfEdgeView::OnObjectsIcosahedron()
{
	m_bCube = FALSE;
	m_bTorus = FALSE;
	m_bTeapot = FALSE;
	m_bIcosahedron = TRUE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// 环
void CHalfEdgeView::OnObjectsTorus()
{
	m_bCube = FALSE;
	m_bTorus = TRUE;
	m_bTeapot = FALSE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// 简单立方体
void CHalfEdgeView::OnObjectsSimplecube()
{
	m_bCube = FALSE;
	m_bTorus = FALSE;
	m_bTeapot = FALSE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = TRUE;
	InvalidateRect(NULL, FALSE);
}

void CHalfEdgeView::display()
{
	if (m_bPoint == TRUE)
	{
		glPointSize(3.0f);
		glBegin(GL_POINTS);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glEnd();
	}
	if (m_bLine == TRUE)
	{
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glEnd();
	}
	if (m_bTriangle == TRUE)
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(2.0f, 0.0f);
		glVertex2f(0.0f, 2.0f);
		glEnd();
	}
	if (m_bPolygon == TRUE)
	{
		glBegin(GL_POLYGON);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(3.0f, 0.0f);
		glVertex2f(4.0f, 3.0f);
		glVertex2f(1.5f, 6.0f);
		glVertex2f(-1.0f, 3.0f);
		glEnd();
	}
	//Replace the current matrix with Identity Matrix
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(-30.0f, 1.0f, 1.0f, 0.0f);
	//Draw a Cube
	if (m_bCube)
	{
		glutWireCube(1.0f);
	}
	//Draw a Torus
	if (m_bTorus)
	{
		glutWireTorus(0.5f, 1.0f, 50, 50);
	}
	//Draw a Teapot
	if (m_bTeapot)
	{
		glutWireTeapot(1.0f);
	}
	//Draw a Icosahedron
	if (m_bIcosahedron)
	{
		glutWireIcosahedron();
	}
	//Draw a cube by specifying the vertices individually
	if (m_bSimpleCube)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Front Face
		glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();
		//Back Face
		glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();
		//Left Face
		glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glEnd();
		//Right Face
		glBegin(GL_POLYGON);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glEnd();
		//Top Face
		glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
		//Botton Face
		glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
	}
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
	// TODO:  在此添加您专用的创建代码

	// Frame 2:加入初始化方法
	myInit();
	return 0;
}

// Frame 3:
// myInit()
//		初始化DC对象，并为其选择像素格式，据此创建RC对象，最后选择该RC

BOOL CHalfEdgeView::myInit()
{
	// 从客户区DC获得DC，自动构造与析构DC
	m_pDC = new CClientDC(this);
	// 获取DC失败，报错
	if (m_pDC == NULL)
	{
		// Frame 3.1:
		//		char转换为LPCTSTR产生乱码问题解决
		//		char与wchar的转换本质是ansi与Unicode的转换
		//		LPCTSTR是LPCWSTR，W意指wide char
		//		LPCSTR意指char
		char *dCh = "Error Obtaining DC";
		wchar_t *w_str;
		w_str = new wchar_t[19];
		w_str[18] = 0;
		if (!w_str)
			delete []w_str;
		MultiByteToWideChar(CP_ACP, 0, dCh, -1, w_str, 18);
		MessageBox((LPCTSTR)w_str);
		return FALSE;
	}
	//不能设置像素格式
	if (!setupPixelFormat())
	{
		return FALSE;
	}
	//创建RC
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//创建RC失败，报错
	if (m_hRC == 0)
	{
		char *rCh = "Error Obtaining RC";
		wchar_t *w_strc;
		w_strc = new wchar_t[19];
		w_strc[18] = 0;
		if (!w_strc)
			delete[]w_strc;
		MultiByteToWideChar(CP_ACP, 0, rCh, -1, w_strc, 18);
		MessageBox((LPCTSTR)w_strc);
		return FALSE;
	}
	//创建RC Current
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		char *rCh = "Error making RC Current";
		wchar_t *w_strc;
		w_strc = new wchar_t[19];
		w_strc[18] = 0;
		if (!w_strc)
			delete[]w_strc;
		MultiByteToWideChar(CP_ACP, 0, rCh, -1, w_strc, 18);
		MessageBox((LPCTSTR)w_strc);
		return FALSE;
	}
	//背景色定义为黑色
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//
	::glClearDepth(1.0f);
	//深度检测
	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}

// Frame 4:
// setupPixelFormat()
//		设置像素格式

BOOL CHalfEdgeView::setupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // 大小
		1,                              // 版本号
		PFD_DRAW_TO_WINDOW |            // 支持窗口
		PFD_SUPPORT_OPENGL |            // 支持OGL
		PFD_DOUBLEBUFFER,               // 双缓冲模式
		PFD_TYPE_RGBA,                  // RGBA色彩模式
		24,                             // 24-bit颜色深度
		0, 0, 0, 0, 0, 0,               // 
		0,                              // alpha-buffer深度
		0, 0, 0, 0, 0, 0,               // 
		16,                             // z-buffer深度
		0, 0,                           // 
		PFD_MAIN_PLANE,                 // 主图层
		0, 0, 0, 0                      // 
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

// Frame 8:
//		内存泄露问题：释放RC/DC
void CHalfEdgeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码

	// RC non-current
	if (::wglMakeCurrent(0, 0) == FALSE)
	{
		char *rCh = "Could not make RC non-current";
		wchar_t *w_strc;
		w_strc = new wchar_t[19];
		w_strc[18] = 0;
		if (!w_strc)
			delete[]w_strc;
		MultiByteToWideChar(CP_ACP, 0, rCh, -1, w_strc, 18);
		MessageBox((LPCTSTR)w_strc);
	}

	// 删除RC
	if (::wglDeleteContext(m_hRC) == FALSE)
	{
		char *dCh = "Could not delete RC";
		wchar_t *w_str;
		w_str = new wchar_t[19];
		w_str[18] = 0;
		if (!w_str)
			delete[]w_str;
		MultiByteToWideChar(CP_ACP, 0, dCh, -1, w_str, 18);
		MessageBox((LPCTSTR)w_str);
	}
	// 删除DC
	if (m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}

// Frame 5:
//		改变窗口大小的时候使用的函数，相当于ogl的reshape
void CHalfEdgeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码

	GLdouble aspect_ratio; // width/height ratio

	if (cx <= 0 || cy <= 0)
	{
		return;
	}

	// 选择整个客户区
	::glViewport(0, 0, cx, cy);

	// 计算方位角
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	// 切换到PROJECTION,单位化
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	// 透视变换
	::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);

	// 切换到MODELVIEW，单位化
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


// Frame 7:
//		拉伸窗口闪烁问题：Windows不需要再清除背景
BOOL CHalfEdgeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// Old：
	// return CView::OnEraseBkgnd(pDC);
	// Now:
	return TRUE;
}
