
// vtkApp.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "vtkApp.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "vtkDoc.h"
#include "vtkPlaneView.h"
#include "vtkGraphView.h"

//#include <AFXPRIV.H>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkApp

BEGIN_MESSAGE_MAP(CvtkApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CvtkApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CvtkApp::OnFileOpen)
END_MESSAGE_MAP()


// CvtkApp 생성

CvtkApp::CvtkApp()
{
	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("vtkApp.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CvtkApp 개체입니다.

CvtkApp theApp;


// CvtkApp 초기화

BOOL CvtkApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면  AfxInitRichEdit2()가 있어야 합니다.	
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 응용 프로그램의 문서 템플릿을 등록합니다. 문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_VTKVIEW,
		RUNTIME_CLASS(CvtkDoc),
		RUNTIME_CLASS(CChildFrame), // 사용자 지정 MDI 자식 프레임입니다.
		RUNTIME_CLASS(CvtkPlaneView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 주 MDI 프레임 창을 만듭니다.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  MDI 응용 프로그램에서는 m_pMainWnd를 설정한 후 바로 이러한 호출이 발생해야 합니다.

	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//CView* pActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();
	//m_pOldView = pActiveView;
	//m_pNewView = (CView*) new CvtkGraphView;
	//if (NULL == m_pNewView)
	//	return FALSE;

	//CDocument* pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();

	//// Initialize a CCreateContext to point to the active document.
	//// With this context, the new view is added to the document
	//// when the view is created in CView::OnCreate().
	//CCreateContext newContext;
	//newContext.m_pNewViewClass = NULL;
	//newContext.m_pNewDocTemplate = NULL;
	//newContext.m_pLastView = NULL;
	//newContext.m_pCurrentFrame = NULL;
	//newContext.m_pCurrentDoc = pCurrentDoc;

	//// The ID of the initial active view is AFX_IDW_PANE_FIRST.
	//// Incrementing this value by one for additional views works
	//// in the standard document/view case but the technique cannot
	//// be extended for the CSplitterWnd case.
	//UINT viewID = AFX_IDW_PANE_FIRST + 1;
	//CRect rect(0, 0, 0, 0); // Gets resized later.

	//// Create the new view. In this example, the view persists for
	//// the life of the application. The application automatically
	//// deletes the view when the application is closed.
	//m_pNewView->Create(NULL, _T("AnyWindowName"), WS_CHILD, rect, m_pMainWnd, viewID, &newContext);

	//// When a document template creates a view, the WM_INITIALUPDATE
	//// message is sent automatically. However, this code must
	//// explicitly send the message, as follows.
	//m_pNewView->SendMessage(WM_INITIALUPDATE, 0, 0);

	// 주 창이 초기화되었으므로 이를 표시하고 업데이트합니다.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CvtkApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	return CWinApp::ExitInstance();
}

// CvtkApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CvtkApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CvtkApp 메시지 처리기





void CvtkApp::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("The application could not open new files."), NULL, MB_ICONERROR);
}
