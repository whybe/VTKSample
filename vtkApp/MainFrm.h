
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	
	CMultiDocTemplate *PlaneViewTemplate;
	CMultiDocTemplate *ListViewTemplate;
	CMultiDocTemplate *GraphViewTemplate;

// ������ �޽��� �� �Լ�
protected:
	CDocument* GetCurrentDocument();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnVtkPlane();
	afx_msg void OnvtkList();
	afx_msg void OnvtkGraph();
	afx_msg LRESULT OnThreadDone(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThumbnail(WPARAM wParam, LPARAM lParam);
};


