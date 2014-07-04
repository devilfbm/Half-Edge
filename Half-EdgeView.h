
// Half-EdgeView.h : CHalfEdgeView 类的接口
//

#pragma once


class CHalfEdgeView : public CView
{
protected: // 仅从序列化创建
	CHalfEdgeView();
	DECLARE_DYNCREATE(CHalfEdgeView)    

// Frame 1：基本的数据结构与方法
protected:
	HGLRC m_hRC;    //渲染上下文
	CDC* m_pDC;        //设备上下文
	
// MyInit() 初始化函数SetupRC()
public:
	BOOL myInit();    
	
// 设置pixel format
public:
	BOOL setupPixelFormat();    
	
// 绘制函数
public:
	void display();            

// Frame 9:
//		基本图元状态
protected:

// Frame 14:
//		鼠标控制

	GLfloat m_xAngle;
	GLfloat m_yAngle;
	GLfloat m_xPos;
	GLfloat m_yPos;
	CPoint m_MouseDownPoint;

// Frame 10:
//		事件处理函数
public:

	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

// 特性
public:
	CHalfEdgeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CHalfEdgeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnButton32772();
	afx_msg void OnButton32782();
	afx_msg void OnButton32784();
	afx_msg void OnButton32785();
	afx_msg void OnButton32787();
	afx_msg void OnButton32788();
};

#ifndef _DEBUG  // Half-EdgeView.cpp 中的调试版本
inline CHalfEdgeDoc* CHalfEdgeView::GetDocument() const
   { return reinterpret_cast<CHalfEdgeDoc*>(m_pDocument); }
#endif

