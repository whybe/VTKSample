
// CvtkApp.h : vtkApp ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CvtkApp:
// �� Ŭ������ ������ ���ؼ��� vtkApp.cpp�� �����Ͻʽÿ�.
//

class CvtkApp : public CWinApp
{
public:
	CvtkApp();

	//CView* m_pOldView;
	//CView* m_pNewView;
	//CView* SwitchView();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
};

extern CvtkApp theApp;
