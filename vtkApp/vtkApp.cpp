
// vtkApp.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CvtkApp::OnFileOpen)
END_MESSAGE_MAP()


// CvtkApp ����

CvtkApp::CvtkApp()
{
	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("vtkApp.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CvtkApp ��ü�Դϴ�.

CvtkApp theApp;


// CvtkApp �ʱ�ȭ

BOOL CvtkApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_VTKVIEW,
		RUNTIME_CLASS(CvtkDoc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CvtkPlaneView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
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

	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CvtkApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	return CWinApp::ExitInstance();
}

// CvtkApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CvtkApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CvtkApp �޽��� ó����





void CvtkApp::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("The application could not open new files."), NULL, MB_ICONERROR);
}
