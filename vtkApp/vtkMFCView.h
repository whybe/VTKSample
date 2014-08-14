#pragma once


// vtkMFCView 뷰입니다.

class vtkMFCDocument;
#include <vtkWindow.h>

class vtkMFCView : public CView
{
	DECLARE_DYNCREATE(vtkMFCView)

protected:
	vtkMFCView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~vtkMFCView();

public:
	vtkMFCDocument* GetDocument() const;
	virtual vtkWindow *GetVTKWindow() {return NULL;};
	virtual void SetupMemoryRendering(int x, int y, HDC prn) {}
	virtual void ResumeScreenRendering() {}
	virtual unsigned char *GetMemoryData() {return NULL;};

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditCopy();
};

#ifndef _DEBUG  // vtkMFCView.cpp의 디버그 버전
inline vtkMFCDocument* vtkMFCView::GetDocument() const
   { return reinterpret_cast<vtkMFCDocument*>(m_pDocument); }
#endif

