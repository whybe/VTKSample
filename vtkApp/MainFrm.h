
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	
	CMultiDocTemplate *PlaneViewTemplate;
	CMultiDocTemplate *ListViewTemplate;
	CMultiDocTemplate *GraphViewTemplate;

// 생성된 메시지 맵 함수
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


