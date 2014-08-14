#pragma once


// vtkMFCRenderView ���Դϴ�.

#include "vtkMFCView.h"

class vtkMFCRenderView : public vtkMFCView
{
	DECLARE_DYNCREATE(vtkMFCRenderView)

protected:
	vtkRenderer *Renderer;
	vtkWin32OpenGLRenderWindow *RenderWindow;
	vtkWin32RenderWindowInteractor *Interactor;

protected:
	vtkMFCRenderView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~vtkMFCRenderView();

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
};


