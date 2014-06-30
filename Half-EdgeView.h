
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
	BOOL m_bPoint;
	BOOL m_bLine;
	BOOL m_bPolygon;
	BOOL m_bTriangle;
	BOOL m_bCube;
	BOOL m_bTorus;
	BOOL m_bTeapot;
	BOOL m_bIcosahedron;
	BOOL m_bSimpleCube;

// Frame 10:
//		事件处理函数
public:
	void OnObjectsTeapot();
	void OnObjectsCube();
	void OnObjectsIcosahedron();
	void OnObjectsTorus();
	void OnObjectsSimplecube();


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
};

#ifndef _DEBUG  // Half-EdgeView.cpp 中的调试版本
inline CHalfEdgeDoc* CHalfEdgeView::GetDocument() const
   { return reinterpret_cast<CHalfEdgeDoc*>(m_pDocument); }
#endif

