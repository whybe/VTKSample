// vtkMFCView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "vtkApp.h"
#include "vtkMFCView.h"
#include "vtkMFCDocument.h"


// vtkMFCView

IMPLEMENT_DYNCREATE(vtkMFCView, CView)

vtkMFCView::vtkMFCView()
{

}

vtkMFCView::~vtkMFCView()
{
}

BEGIN_MESSAGE_MAP(vtkMFCView, CView)
	ON_COMMAND(ID_EDIT_COPY, &vtkMFCView::OnEditCopy)
END_MESSAGE_MAP()


// vtkMFCView �׸����Դϴ�.

void vtkMFCView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// vtkMFCView �����Դϴ�.

#ifdef _DEBUG
void vtkMFCView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void vtkMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// vtkMFCView �޽��� ó�����Դϴ�.


void vtkMFCView::OnEditCopy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	LPBITMAPINFOHEADER  lpbi;       // pointer to BITMAPINFOHEADER
	DWORD               dwLen;      // size of memory block
	HANDLE              hDIB = NULL;  // handle to DIB, temp handle
	vtkWindow *vtkWin = this->GetVTKWindow();
	int *size = vtkWin->GetSize();
	int dataWidth = ((size[0]*3+3)/4)*4;

	if (OpenClipboard())
	{
		BeginWaitCursor();
		EmptyClipboard();

		dwLen = sizeof(BITMAPINFOHEADER) + dataWidth*size[1];
		hDIB = ::GlobalAlloc(GHND, dwLen);
		lpbi = (LPBITMAPINFOHEADER) ::GlobalLock(hDIB);

		lpbi->biSize = sizeof(BITMAPINFOHEADER);
		lpbi->biWidth = size[0];
		lpbi->biHeight = size[1];
		lpbi->biPlanes = 1;
		lpbi->biBitCount = 24;
		lpbi->biCompression = BI_RGB;
		lpbi->biClrUsed = 0;
		lpbi->biClrImportant = 0;
		lpbi->biSizeImage = dataWidth*size[1];

		this->SetupMemoryRendering(size[0],size[1],
			this->GetDC()->GetSafeHdc());
		vtkWin->Render();

		memcpy((LPSTR)lpbi + lpbi->biSize,
			this->GetMemoryData(),dataWidth*size[1]);

		SetClipboardData (CF_DIB, hDIB);
		::GlobalUnlock(hDIB);
		CloseClipboard();
		this->ResumeScreenRendering();
		EndWaitCursor();
}
