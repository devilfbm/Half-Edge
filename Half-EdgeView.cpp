
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

//���ղ���
//W = 0.0f ����Զ��
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

// CHalfEdgeView ����/����
// Frame 9:
//		���ñ��
CHalfEdgeView::CHalfEdgeView()
{
	// TODO:  �ڴ˴���ӹ������


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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	// Flush
	glFinish();
	// ����buffer��
	SwapBuffers(m_pDC->GetSafeHdc());
	Invalidate();
}

// Frame 10(�Ѿ�����):
//		���������¼��������

void CHalfEdgeView::display()
{
	glLoadIdentity();
	glTranslatef(m_xPos, m_yPos - 1, -5.0f);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	// Frame 13:
	//		���doc���ٿ�sourceTree;
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//
	glClearDepth(1.0f);
	//��ȼ��
	glEnable(GL_DEPTH_TEST);
	//������
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//����ģ��
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

// Frame 15:
//		�������¼�����
void CHalfEdgeView::OnButton32772()
{
	// TODO:  �ڴ���������������
	m_xPos -= 0.1f;
}


void CHalfEdgeView::OnButton32782()
{
	// TODO:  �ڴ���������������
	m_yPos += 0.1f;
}


void CHalfEdgeView::OnButton32784()
{
	// TODO:  �ڴ���������������
	m_xPos += 0.1f;
}


void CHalfEdgeView::OnButton32785()
{
	// TODO:  �ڴ���������������
	m_yPos -= 0.1f;
}


void CHalfEdgeView::OnButton32787()
{
	// TODO:  �ڴ���������������
	m_yAngle -= 5.0f;
}


void CHalfEdgeView::OnButton32788()
{
	// TODO:  �ڴ���������������
	m_yAngle += 5.0f;
}
