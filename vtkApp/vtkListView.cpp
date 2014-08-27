// vtkListView.cpp : 구현 파일입니다.
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


// CvtkListView 진단입니다.

#ifdef _DEBUG
void CvtkListView::AssertValid() const
{
	CListView::AssertValid();
}

void CvtkListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CvtkDoc* CvtkListView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkListView 메시지 처리기입니다.


void CvtkListView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


BOOL CvtkListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CListView::PreCreateWindow(cs);
}


BOOL CvtkListView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CListView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CvtkListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
