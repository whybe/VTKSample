
// vtkAppView.cpp : CvtkAppView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif

#include "vtkAppDoc.h"
#include "vtkAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkAppView

IMPLEMENT_DYNCREATE(CvtkAppView, CView)

BEGIN_MESSAGE_MAP(CvtkAppView, CView)
END_MESSAGE_MAP()

// CvtkAppView ����/�Ҹ�

CvtkAppView::CvtkAppView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CvtkAppView::~CvtkAppView()
{
}

BOOL CvtkAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CvtkAppView �׸���

void CvtkAppView::OnDraw(CDC* /*pDC*/)
{
	CvtkAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CvtkAppView ����

#ifdef _DEBUG
void CvtkAppView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkAppDoc* CvtkAppView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkAppDoc)));
	return (CvtkAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkAppView �޽��� ó����
