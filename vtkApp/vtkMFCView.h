#pragma once


// vtkMFCView ���Դϴ�.

class vtkMFCDocument;
#include <vtkWindow.h>

class vtkMFCView : public CView
{
	DECLARE_DYNCREATE(vtkMFCView)

protected:
	vtkMFCView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~vtkMFCView();

public:
	vtkMFCDocument* GetDocument() const;
	virtual vtkWindow *GetVTKWindow() {return NULL;};
	virtual void SetupMemoryRendering(int x, int y, HDC prn) {}
	virtual void ResumeScreenRendering() {}
	virtual unsigned char *GetMemoryData() {return NULL;};

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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

#ifndef _DEBUG  // vtkMFCView.cpp�� ����� ����
inline vtkMFCDocument* vtkMFCView::GetDocument() const
   { return reinterpret_cast<vtkMFCDocument*>(m_pDocument); }
#endif

