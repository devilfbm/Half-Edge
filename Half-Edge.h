
// Half-Edge.h : Half-Edge Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CHalfEdgeApp:
// �йش����ʵ�֣������ Half-Edge.cpp
//

class CHalfEdgeApp : public CWinApp
{

public:
	CHalfEdgeApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileMyopen();
};

extern CHalfEdgeApp theApp;
