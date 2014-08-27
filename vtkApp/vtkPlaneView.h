
// CvtkPlaneView.h : CvtkPlaneView Ŭ������ �������̽�
//

#pragma once

#include <vtkSmartPointer.h>
#include <vtkMFCWindow.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
//#include "vtkMouseInteractorStyle.h"
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkNamedColors.h>
#include <vtkCamera.h>

class vtkMouseInteractorStyle;

class CvtkPlaneView : public CView
{
protected: // serialization������ ��������ϴ�.
	CvtkPlaneView();
	DECLARE_DYNCREATE(CvtkPlaneView)

// Ư���Դϴ�.
public:
	CvtkDoc* GetDocument() const;

// �۾��Դϴ�.
public:

protected:
	vtkMFCWindow* MFCWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkMouseInteractorStyle> mouseInteractorStyle;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderer> selectedRenderer;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkPolyDataMapper> polyDataMapper;
	vtkSmartPointer<vtkNamedColors> namedColors;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CvtkPlaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // vtkAppView.cpp�� ����� ����
inline CvtkDoc* CvtkPlaneView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif

