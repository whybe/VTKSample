
// CvtkGraphView.h : CvtkGraphView Ŭ������ �������̽�
//

#pragma once

#include <vtkMFCWindow.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
//#include <vtkTriangleFilter.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
//#include "vtkMouseInteractorStyle.h"

class vtkMouseInteractorStyle;

class CvtkGraphView : public CView
{
public:
	CvtkGraphView();
protected: // serialization������ ��������ϴ�.
	DECLARE_DYNCREATE(CvtkGraphView)

// Ư���Դϴ�.
public:
	CvtkDoc* GetDocument() const;

	vtkSmartPointer<vtkPlaneSource> planeSource;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkMouseInteractorStyle> style;

// �۾��Դϴ�.
public:

protected:
	vtkMFCWindow* MFCWindow;
	//vtkSmartPointer<vtkRenderer> Renderer;
	//vtkSmartPointer<vtkActor> Actor;
	//vtkSmartPointer<vtkPolyDataMapper> PolyDataMapper;
	//vtkSmartPointer<vtkNamedColors> NamedColors;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CvtkGraphView();
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
inline CvtkDoc* CvtkGraphView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif

