
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "vtkApp.h"
#include "vtkDoc.h"
#include "vtkPlaneView.h"
#include "vtkListView.h"
#include "vtkGraphView.h"
#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VTK_GRAPH, &CMainFrame::OnvtkGraph)
	ON_COMMAND(ID_VTK_LIST, &CMainFrame::OnvtkList)
	ON_MESSAGE(WM_THREADDONE, &CMainFrame::OnThreadDone)
	ON_MESSAGE(WM_THUMBNAIL, &CMainFrame::OnThumbnail)
	ON_COMMAND(ID_VTK_PLANE, &CMainFrame::OnVtkPlane)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	GraphViewTemplate = NULL;
	ListViewTemplate = NULL;
}

CMainFrame::~CMainFrame()
{
	delete GraphViewTemplate;
	delete ListViewTemplate;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����


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

void CMainFrame::OnVtkPlane()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(PlaneViewTemplate == NULL)
		PlaneViewTemplate = new CMultiDocTemplate(IDR_VTKVIEW,
		RUNTIME_CLASS(CvtkDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CvtkPlaneView));
	ASSERT(ListViewTemplate != NULL);
	if(ListViewTemplate == NULL)
		return; // internal error should not occur

	CvtkDoc *doc = (CvtkDoc *)GetCurrentDocument();
	ASSERT(doc != NULL);
	if(doc == NULL)
		return; // should not be possible

	CFrameWnd * frame = PlaneViewTemplate->CreateNewFrame(doc, NULL);
	ASSERT(frame != NULL);
	if(frame != NULL)
	{ /* frame created */
		frame->InitialUpdateFrame(doc, TRUE);
	} /* frame created */
}

void CMainFrame::OnvtkList()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(ListViewTemplate == NULL)
		ListViewTemplate = new CMultiDocTemplate(IDR_VTKVIEW,
		RUNTIME_CLASS(CvtkDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CvtkListView));
	ASSERT(ListViewTemplate != NULL);
	if(ListViewTemplate == NULL)
		return; // internal error should not occur

	CvtkDoc *doc = (CvtkDoc *)GetCurrentDocument();
	ASSERT(doc != NULL);
	if(doc == NULL)
		return; // should not be possible

	CFrameWnd * frame = ListViewTemplate->CreateNewFrame(doc, NULL);
	ASSERT(frame != NULL);
	if(frame != NULL)
	{ /* frame created */
		frame->InitialUpdateFrame(doc, TRUE);
	} /* frame created */
}

void CMainFrame::OnvtkGraph()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(GraphViewTemplate == NULL)
		GraphViewTemplate = new CMultiDocTemplate(IDR_VTKVIEW,
		RUNTIME_CLASS(CvtkDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CvtkGraphView));
	ASSERT(GraphViewTemplate != NULL);
	if(GraphViewTemplate == NULL)
		return; // internal error should not occur

	CvtkDoc *doc = (CvtkDoc *)GetCurrentDocument();
	ASSERT(doc != NULL);
	if(doc == NULL)
		return; // should not be possible

	CFrameWnd * frame = GraphViewTemplate->CreateNewFrame(doc, NULL);
	ASSERT(frame != NULL);
	if(frame != NULL)
	{ /* frame created */
		frame->InitialUpdateFrame(doc, TRUE);
	} /* frame created */
}

LRESULT CMainFrame::OnThreadDone(WPARAM wParam, LPARAM lParam)
{
	//CvtkDoc *doc = (CvtkDoc *)GetCurrentDocument();
	CvtkDoc *doc = (CvtkDoc *)lParam;
	ASSERT(doc != NULL);
	if(doc->m_bDo != TRUE)
	{
		std::cout << "Thread Force Terminate" << std::endl;
		return FALSE;
	}

	doc->UpdatePlaneSource();
	doc->UpdateAllViews(NULL);
	std::cout << "UpdatePlaneSource" << std::endl;

	LRESULT ret = SendMessage(WM_COMMAND, ID_VTK_LIST, 0);
	std::cout << "SendMessage(WM_COMMAND, ID_VTK_LIST) : " << ret << std::endl;
	
	doc->StartThread(doc->OffScreenRenderingThreadFunc);

	return TRUE;
}

LRESULT CMainFrame::OnThumbnail(WPARAM wParam, LPARAM lParam)
{
	int frameNum = (int)wParam;
	CvtkDoc *doc = (CvtkDoc *)lParam;
	ASSERT(doc != NULL);

	CvtkListView *view = (CvtkListView*)(doc->GetView(RUNTIME_CLASS(CvtkListView)));
	ASSERT(view != NULL);

	view->Thumbnail(frameNum);

	std::cout << "Thumbnail : " << frameNum << std::endl;

	return TRUE;
}

