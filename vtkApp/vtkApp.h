
// vtkApp.h : vtkApp ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CvtkAppApp:
// �� Ŭ������ ������ ���ؼ��� vtkApp.cpp�� �����Ͻʽÿ�.
//

class CvtkAppApp : public CWinApp
{
public:
	CvtkAppApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CvtkAppApp theApp;
