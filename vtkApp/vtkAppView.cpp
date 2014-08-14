
// vtkAppView.cpp : CvtkAppView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CvtkAppView 생성/소멸

CvtkAppView::CvtkAppView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CvtkAppView::~CvtkAppView()
{
}

BOOL CvtkAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CvtkAppView 그리기

void CvtkAppView::OnDraw(CDC* /*pDC*/)
{
	CvtkAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CvtkAppView 진단

#ifdef _DEBUG
void CvtkAppView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkAppDoc* CvtkAppView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkAppDoc)));
	return (CvtkAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkAppView 메시지 처리기
