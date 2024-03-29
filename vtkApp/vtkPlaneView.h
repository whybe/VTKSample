
// CvtkPlaneView.h : CvtkPlaneView 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CvtkPlaneView();
	DECLARE_DYNCREATE(CvtkPlaneView)

// 특성입니다.
public:
	CvtkDoc* GetDocument() const;

// 작업입니다.
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

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CvtkPlaneView();
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
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // vtkAppView.cpp의 디버그 버전
inline CvtkDoc* CvtkPlaneView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif

