
// vtkAppView.h : CvtkAppView Ŭ������ �������̽�
//

#pragma once


class CvtkAppView : public CView
{
protected: // serialization������ ��������ϴ�.
	CvtkAppView();
	DECLARE_DYNCREATE(CvtkAppView)

// Ư���Դϴ�.
public:
	CvtkAppDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CvtkAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // vtkAppView.cpp�� ����� ����
inline CvtkAppDoc* CvtkAppView::GetDocument() const
   { return reinterpret_cast<CvtkAppDoc*>(m_pDocument); }
#endif

