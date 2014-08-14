
// CvtkSubView.h : CvtkSubView Ŭ������ �������̽�
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
#include "vtkMouseInteractorStyle.h"

class CvtkSubView : public CView
{
public:
	CvtkSubView();
protected: // serialization������ ��������ϴ�.
	DECLARE_DYNCREATE(CvtkSubView)

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
	virtual ~CvtkSubView();
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

#ifndef _DEBUG  // vtkWindowView.cpp�� ����� ����
inline CvtkDoc* CvtkSubView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif

