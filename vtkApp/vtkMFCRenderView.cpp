// vtkMFCRenderView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "vtkApp.h"
#include "vtkMFCRenderView.h"


// vtkMFCRenderView

IMPLEMENT_DYNCREATE(vtkMFCRenderView, CView)

vtkMFCRenderView::vtkMFCRenderView()
{

}

vtkMFCRenderView::~vtkMFCRenderView()
{
}

BEGIN_MESSAGE_MAP(vtkMFCRenderView, CView)
END_MESSAGE_MAP()


// vtkMFCRenderView 그리기입니다.

void vtkMFCRenderView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// vtkMFCRenderView 진단입니다.

#ifdef _DEBUG
void vtkMFCRenderView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void vtkMFCRenderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// vtkMFCRenderView 메시지 처리기입니다.
