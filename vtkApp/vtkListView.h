#pragma once


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
	virtual void OnDraw(CDC* /*pDC*/);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
protected:
	CImageList m_ImageList;
};

#ifndef _DEBUG
inline CvtkDoc* CvtkListView::GetDocument() const
   { return reinterpret_cast<CvtkDoc*>(m_pDocument); }
#endif
