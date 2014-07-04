
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

//光照参数
//W = 0.0f 无穷远光
GLfloat LightPos[4] = { .0f, .0f, .0f, 1.0f };
GLfloat SunLightPos[4] = { .0f, 5.0f, .0f, 1.0f };
GLfloat NoLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat LowLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat BrightLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat EmissiveLight[] = { 1.0f, 0.87f, 0.27f, 0.5f };
GLfloat SunEmissiveLight[] = { 0.5f, 0.37f, 0.27f, 0.5f };

// CHalfEdgeView

IMPLEMENT_DYNCREATE(CHalfEdgeView, CView)

BEGIN_MESSAGE_MAP(CHalfEdgeView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BUTTON32772, &CHalfEdgeView::OnButton32772)
	ON_COMMAND(ID_BUTTON32782, &CHalfEdgeView::OnButton32782)
	ON_COMMAND(ID_BUTTON32784, &CHalfEdgeView::OnButton32784)
	ON_COMMAND(ID_BUTTON32785, &CHalfEdgeView::OnButton32785)
	ON_COMMAND(ID_BUTTON32787, &CHalfEdgeView::OnButton32787)
	ON_COMMAND(ID_BUTTON32788, &CHalfEdgeView::OnButton32788)
END_MESSAGE_MAP()

// CHalfEdgeView 构造/析构
// Frame 9:
//		设置标记
CHalfEdgeView::CHalfEdgeView()
{
	// TODO:  在此处添加构造代码


	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	// Flush
	glFinish();
	// 交换buffer？
	SwapBuffers(m_pDC->GetSafeHdc());
	Invalidate();
}

// Frame 10(已经弃用):
//		描绘物体的事件处理程序

void CHalfEdgeView::display()
{
	glLoadIdentity();
	glTranslatef(m_xPos, m_yPos - 1, -5.0f);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	// Frame 13:
	//		获得doc并操控sourceTree;
	CHalfEdgeDoc *pDoc = GetDocument();
	if (pDoc->sourceManager->count != 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		long nodesSize = (pDoc->sourceManager->out_vertices_list)[0].size();
		glBegin(GL_TRIANGLES);
		for (long i = 0; i < nodesSize; i++)
		{
			glNormal3f((pDoc->sourceManager->out_normals_list)[0][i].x, (pDoc->sourceManager->out_normals_list)[0][i].y, (pDoc->sourceManager->out_normals_list)[0][i].z);
			glVertex3f((pDoc->sourceManager->out_vertices_list)[0][i].x, (pDoc->sourceManager->out_vertices_list)[0][i].y, (pDoc->sourceManager->out_vertices_list)[0][i].z);
		}
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//
	glClearDepth(1.0f);
	//深度检测
	glEnable(GL_DEPTH_TEST);
	//反走样
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//光照模型
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, NoLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LowLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, BrightLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, BrightLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, EmissiveLight);
	glLightfv(GL_LIGHT1, GL_EMISSION, EmissiveLight);	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
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

// Frame 15:
//		工具栏事件处理
void CHalfEdgeView::OnButton32772()
{
	// TODO:  在此添加命令处理程序代码
	m_xPos -= 0.1f;
}


void CHalfEdgeView::OnButton32782()
{
	// TODO:  在此添加命令处理程序代码
	m_yPos += 0.1f;
}


void CHalfEdgeView::OnButton32784()
{
	// TODO:  在此添加命令处理程序代码
	m_xPos += 0.1f;
}


void CHalfEdgeView::OnButton32785()
{
	// TODO:  在此添加命令处理程序代码
	m_yPos -= 0.1f;
}


void CHalfEdgeView::OnButton32787()
{
	// TODO:  在此添加命令处理程序代码
	m_yAngle -= 5.0f;
}


void CHalfEdgeView::OnButton32788()
{
	// TODO:  在此添加命令处理程序代码
	m_yAngle += 5.0f;
}
