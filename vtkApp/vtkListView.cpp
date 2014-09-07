// vtkListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif
#include "vtkListView.h"
#include "vtkDoc.h"


// CvtkListView

IMPLEMENT_DYNCREATE(CvtkListView, CListView)

BEGIN_MESSAGE_MAP(CvtkListView, CListView)
END_MESSAGE_MAP()


CvtkListView::CvtkListView()
{
	m_ImageList = new CImageList;
}

CvtkListView::~CvtkListView()
{
	if (m_ImageList) {
		m_ImageList->DeleteImageList();
		delete m_ImageList;
		m_ImageList = NULL;
	}

	if (m_pThread)
		StopThread();
}

// CvtkListView 진단입니다.

#ifdef _DEBUG
void CvtkListView::AssertValid() const
{
	CListView::AssertValid();
}

void CvtkListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CvtkDoc* CvtkListView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkListView 메시지 처리기입니다.

BOOL CvtkListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CListView::PreCreateWindow(cs);
}
   

BOOL CvtkListView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//dwStyle |= LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_SINGLESEL|LVS_AUTOARRANGE;
	return CListView::Create(lpszClassName, lpszWindowName, dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_SINGLESEL|LVS_AUTOARRANGE, rect, pParentWnd, nID, pContext);
}


void CvtkListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CListCtrl& ListCtrl = GetListCtrl();

	// Initialize Imaget List and Attach it to ListCtrl
	//m_ImageList->Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, GetDocument()->frameCount, 0);
	m_ImageList->Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	//HBITMAP hbmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	//ASSERT(hbmp!=NULL);
	//Bitmap* pBmp = Bitmap::FromHBITMAP(hbmp,NULL);
	//ASSERT(pBmp->GetLastStatus() == Ok);

	//m_ImageList->Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	//for(int i = 0; i < GetDocument()->frameCount; i++) {
	//	m_ImageList->Add(pBmp, NULL);
	//}
	ListCtrl.SetImageList(m_ImageList, LVSIL_NORMAL);

	m_ImageList->SetImageCount(GetDocument()->frameCount);

	ListCtrl.SetRedraw(FALSE);
	for(int frameNum = 0; frameNum < GetDocument()->frameCount; frameNum++)
	{
		CString str;
		str.Format(_T("frame%d"), frameNum);
		ListCtrl.InsertItem(frameNum, str, frameNum);
	}
	ListCtrl.SetRedraw(TRUE);
	ListCtrl.Invalidate();
}

void CvtkListView::LoadThumbnail(int frameNum)
{
	CListCtrl& ListCtrl = GetListCtrl();

	vtkUnsignedCharArray *imageArray = GetDocument()->m_imageArray.GetAt(frameNum);

	IStream *pStream = NULL;
	HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
	if(SUCCEEDED(hr))
	{
		ULONG ulWriteByte = 0;
		ULARGE_INTEGER sz;
		sz.HighPart = 0;
		sz.LowPart = imageArray->GetDataSize();

		pStream->SetSize(sz);
		pStream->Write(imageArray->GetVoidPointer(0), imageArray->GetDataSize(), &ulWriteByte);

		//CString str;
		//str.Format(_T("frame%d.png"), frameNum);
		CImage image;
		image.Load(pStream);
		//image.Save(str, Gdiplus::ImageFormatPNG);
		//CBitmap bitmap;
		//bitmap.Attach(image.Detach());
		//m_ImageList->Replace(frameNum, &bitmap, NULL);
		m_ImageList->Replace(frameNum, CBitmap::FromHandle(image), NULL);
		//bitmap.DeleteObject();
		//delete image;
		

		pStream->Release();
	}

	// Redraw only a current item for removing flickering and fast speed.
	ListCtrl.RedrawItems(frameNum, frameNum);
	ListCtrl.Invalidate();
	//ListCtrl.Update(frameNum);
	//ListCtrl.UpdateWindow();
}


void CvtkListView::Thumbnail(int frameNum){

	StartThread(ThreadFunc, frameNum);
}

UINT CvtkListView::ThreadFunc(LPVOID pThreadParam){
	LISTVIEWTHREADPARAM *pParam = (LISTVIEWTHREADPARAM *)pThreadParam;

	CvtkListView *view = (CvtkListView *)pParam->pWnd;
	int frameNum = (int)pParam->frameNum;
	delete pParam;

	// TODO
	view->LoadThumbnail(frameNum);

	return 0;
}

void CvtkListView::StartThread(UINT (*fn)(LPVOID), int frameNum){
	LISTVIEWTHREADPARAM *pThreadParam = new LISTVIEWTHREADPARAM;
	pThreadParam->pWnd = (CWnd *)this;
	pThreadParam->frameNum = frameNum;

	m_pThread = AfxBeginThread(fn, pThreadParam);

	m_bDo = TRUE;
	std::cout << "StartThread" << std::endl;
}

void CvtkListView::StopThread(){
	m_bDo = FALSE;
	std::cout << "StopThread" << std::endl;

	Sleep(100);

	if (::WaitForSingleObject(m_pThread->m_hThread, INFINITE))
	{
		m_pThread = NULL;

		// TODO
	}
}
