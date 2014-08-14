
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "vtkApp.h"
#include "vtkDoc.h"
#include "vtkSubView.h"
#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_SUBVIEW, &CMainFrame::OnWindowSubview)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	SubViewTemplate = NULL;
}

CMainFrame::~CMainFrame()
{
	delete SubViewTemplate;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기


CDocument * CMainFrame::GetCurrentDocument()
{
	CMDIFrameWnd * frame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	if(frame == NULL)
		return NULL;
	CMDIChildWnd * child = (CMDIChildWnd *)frame->GetActiveFrame();
	if(child == NULL)
		return NULL;
	CView * view = child->GetActiveView();
	if(view == NULL)
		return NULL;
	CDocument * doc = view->GetDocument();
	return doc;
} // CMainFrame::GetCurrentDocument

void CMainFrame::OnWindowSubview()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(SubViewTemplate == NULL)
		SubViewTemplate = new CMultiDocTemplate(IDR_VTKSUBVIEW,
		RUNTIME_CLASS(CvtkDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CvtkSubView));
	ASSERT(SubViewTemplate != NULL);
	if(SubViewTemplate == NULL)
		return; // internal error should not occur

	CvtkDoc *doc = (CvtkDoc *)GetCurrentDocument();
	ASSERT(doc != NULL);
	if(doc == NULL)
		return; // should not be possible

	CFrameWnd * frame = SubViewTemplate->CreateNewFrame(doc, NULL);
	ASSERT(frame != NULL);
	if(frame != NULL)
	{ /* frame created */
		frame->InitialUpdateFrame(doc, TRUE);
	} /* frame created */

}
