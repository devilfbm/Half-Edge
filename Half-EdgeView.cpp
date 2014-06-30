
// Half-EdgeView.cpp : CHalfEdgeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CHalfEdgeView ����/����
// Frame 9:
//		���ñ��
CHalfEdgeView::CHalfEdgeView()
{
	// TODO:  �ڴ˴���ӹ������
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	// Frame 0: OpenGL����ʹ�����±��
	//		WS_CLIPCHILDREN���ü��Ӵ���
	//						 ���ڸ����ڻ��Ƶ�ʱ�򣬸������ϻ���һ���Ӵ��ڵĻ����Ӵ������򸸴��ھͲ�������ơ�
	//		WS_CLIPSIBLINGS���ü��ֵܴ���
	//							���е�overlapped��popup���Ĵ��ڣ�����WS_CLIPSIBLINGS ���ԡ�
	//							Ҳ����˵������Ĵ��ڣ�����ȥ����WS_CLIPSIBLINGS ���Եģ����������ص����ֵܴ��ڻ�ͼ��
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CHalfEdgeView ����
// Frame 6:
void CHalfEdgeView::OnDraw(CDC* /*pDC*/)
{
	CHalfEdgeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

	// 
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	// Flush
	::glFinish();
	// ����
	::SwapBuffers(m_pDC->GetSafeHdc());
}

// Frame 10:
//		���������¼��������
// ���
void CHalfEdgeView::OnObjectsTeapot()
{
	m_bCube = FALSE;
	m_bTorus = FALSE;
	m_bTeapot = TRUE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// ������
void CHalfEdgeView::OnObjectsCube()
{
	m_bCube = TRUE;
	m_bTorus = FALSE;
	m_bTeapot = FALSE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// ��ʮ����
void CHalfEdgeView::OnObjectsIcosahedron()
{
	m_bCube = FALSE;
	m_bTorus = FALSE;
	m_bTeapot = FALSE;
	m_bIcosahedron = TRUE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// ��
void CHalfEdgeView::OnObjectsTorus()
{
	m_bCube = FALSE;
	m_bTorus = TRUE;
	m_bTeapot = FALSE;
	m_bIcosahedron = FALSE;
	m_bSimpleCube = FALSE;
	InvalidateRect(NULL, FALSE);
}

// ��������
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

// CHalfEdgeView ���

#ifdef _DEBUG
void CHalfEdgeView::AssertValid() const
{
	CView::AssertValid();
}

void CHalfEdgeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHalfEdgeDoc* CHalfEdgeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHalfEdgeDoc)));
	return (CHalfEdgeDoc*)m_pDocument;
}
#endif //_DEBUG


// CHalfEdgeView ��Ϣ�������


int CHalfEdgeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������

	// Frame 2:�����ʼ������
	myInit();
	return 0;
}

// Frame 3:
// myInit()
//		��ʼ��DC���󣬲�Ϊ��ѡ�����ظ�ʽ���ݴ˴���RC�������ѡ���RC

BOOL CHalfEdgeView::myInit()
{
	// �ӿͻ���DC���DC���Զ�����������DC
	m_pDC = new CClientDC(this);
	// ��ȡDCʧ�ܣ�����
	if (m_pDC == NULL)
	{
		// Frame 3.1:
		//		charת��ΪLPCTSTR��������������
		//		char��wchar��ת��������ansi��Unicode��ת��
		//		LPCTSTR��LPCWSTR��W��ָwide char
		//		LPCSTR��ָchar
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
	//�����������ظ�ʽ
	if (!setupPixelFormat())
	{
		return FALSE;
	}
	//����RC
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//����RCʧ�ܣ�����
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
	//����RC Current
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
	//����ɫ����Ϊ��ɫ
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//
	::glClearDepth(1.0f);
	//��ȼ��
	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}

// Frame 4:
// setupPixelFormat()
//		�������ظ�ʽ

BOOL CHalfEdgeView::setupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // ��С
		1,                              // �汾��
		PFD_DRAW_TO_WINDOW |            // ֧�ִ���
		PFD_SUPPORT_OPENGL |            // ֧��OGL
		PFD_DOUBLEBUFFER,               // ˫����ģʽ
		PFD_TYPE_RGBA,                  // RGBAɫ��ģʽ
		24,                             // 24-bit��ɫ���
		0, 0, 0, 0, 0, 0,               // 
		0,                              // alpha-buffer���
		0, 0, 0, 0, 0, 0,               // 
		16,                             // z-buffer���
		0, 0,                           // 
		PFD_MAIN_PLANE,                 // ��ͼ��
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
//		�ڴ�й¶���⣺�ͷ�RC/DC
void CHalfEdgeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������

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

	// ɾ��RC
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
	// ɾ��DC
	if (m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}

// Frame 5:
//		�ı䴰�ڴ�С��ʱ��ʹ�õĺ������൱��ogl��reshape
void CHalfEdgeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������

	GLdouble aspect_ratio; // width/height ratio

	if (cx <= 0 || cy <= 0)
	{
		return;
	}

	// ѡ�������ͻ���
	::glViewport(0, 0, cx, cy);

	// ���㷽λ��
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	// �л���PROJECTION,��λ��
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	// ͸�ӱ任
	::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);

	// �л���MODELVIEW����λ��
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


// Frame 7:
//		���촰����˸���⣺Windows����Ҫ���������
BOOL CHalfEdgeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// Old��
	// return CView::OnEraseBkgnd(pDC);
	// Now:
	return TRUE;
}
