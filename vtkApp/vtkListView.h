#pragma once

typedef struct tagListViewThreadParam
{
	CWnd *pWnd;
	int frameNum;
} LISTVIEWTHREADPARAM;

class CvtkDoc;

class CvtkListView : public CListView
{
	DECLARE_DYNCREATE(CvtkListView)

protected:
	CvtkListView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CvtkListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CvtkDoc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();

	bool m_bDo;
	CWinThread *m_pThread;

	void Thumbnail(int frameNum);
	void LoadThumbnail(int frameNum);
	static UINT ThreadFunc(LPVOID pThreadParam);
	void StartThread(UINT (*fn)(LPVOID), int frameNum);
	void StopThread();

protected:
	CImageList* m_ImageList;		// image list holding the thumbnails
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG
inline CvtkDoc* CvtkListView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif
