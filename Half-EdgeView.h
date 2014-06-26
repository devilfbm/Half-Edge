
// Half-EdgeView.h : CHalfEdgeView ��Ľӿ�
//

#pragma once


class CHalfEdgeView : public CView
{
protected: // �������л�����
	CHalfEdgeView();
	DECLARE_DYNCREATE(CHalfEdgeView)    

// Frame 1�����������ݽṹ�뷽��
protected:
	HGLRC m_hRC;    //��Ⱦ������
	CDC* m_pDC;        //�豸������
	
// MyInit() ��ʼ������SetupRC()
public:
	BOOL myInit();    
	
// ����pixel format
public:
	BOOL setupPixelFormat();    
	
// ���ƺ���
public:
	void display();            

// ����
public:
	CHalfEdgeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CHalfEdgeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // Half-EdgeView.cpp �еĵ��԰汾
inline CHalfEdgeDoc* CHalfEdgeView::GetDocument() const
   { return reinterpret_cast<CHalfEdgeDoc*>(m_pDocument); }
#endif

