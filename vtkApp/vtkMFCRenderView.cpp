// vtkMFCRenderView.cpp : ���� �����Դϴ�.
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


// vtkMFCRenderView �׸����Դϴ�.

void vtkMFCRenderView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// vtkMFCRenderView �����Դϴ�.

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


// vtkMFCRenderView �޽��� ó�����Դϴ�.
