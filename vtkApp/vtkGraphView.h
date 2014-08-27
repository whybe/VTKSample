
// CvtkGraphView.h : CvtkGraphView 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	DECLARE_DYNCREATE(CvtkGraphView)

// 특성입니다.
public:
	CvtkDoc* GetDocument() const;

	vtkSmartPointer<vtkPlaneSource> planeSource;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkMouseInteractorStyle> style;

// 작업입니다.
public:

protected:
	vtkMFCWindow* MFCWindow;
	//vtkSmartPointer<vtkRenderer> Renderer;
	//vtkSmartPointer<vtkActor> Actor;
	//vtkSmartPointer<vtkPolyDataMapper> PolyDataMapper;
	//vtkSmartPointer<vtkNamedColors> NamedColors;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CvtkGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // vtkAppView.cpp의 디버그 버전
inline CvtkDoc* CvtkGraphView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif

