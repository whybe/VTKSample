// vtkListView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "vtkListView.h"
#include "vtkDoc.h"


// CvtkListView

IMPLEMENT_DYNCREATE(CvtkListView, CListView)

CvtkListView::CvtkListView()
{

}

CvtkListView::~CvtkListView()
{
}

BEGIN_MESSAGE_MAP(CvtkListView, CListView)
END_MESSAGE_MAP()


// CvtkListView �����Դϴ�.

#ifdef _DEBUG
void CvtkListView::AssertValid() const
{
	CListView::AssertValid();
}

void CvtkListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CvtkDoc* CvtkListView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkListView �޽��� ó�����Դϴ�.


void CvtkListView::OnDraw(CDC* /*pDC*/)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


BOOL CvtkListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CListView::PreCreateWindow(cs);
}


BOOL CvtkListView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CListView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CvtkListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
