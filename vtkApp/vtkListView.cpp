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
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CLICK, &CvtkListView::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CvtkListView::OnNMDblclk)
END_MESSAGE_MAP()


CvtkListView::CvtkListView()
{
	m_ImageList = new CImageList;

	m_pThread = NULL;
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
	
	//vtkSmartPointer<vtkNamedColors> namedColors = vtkSmartPointer<vtkNamedColors>::New();
	//unsigned char *bgColor = namedColors->GetColor3ub("white_smoke").GetData();

	//ListCtrl.SetBkColor(RGB(bgColor[0], bgColor[1], bgColor[2]));

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

	int listCount = GetDocument()->frameCount + 1;
	m_ImageList->SetImageCount(listCount);

	ListCtrl.SetRedraw(FALSE);

	for(int listNum = 0; listNum < listCount; listNum++)
	{
		if (listNum == 0)
			ListCtrl.InsertItem(0, _T("Total"), 0);
		else
		{
			int frameNum = listNum - 1;

			CString str;
			str.Format(_T("frame%d"), frameNum);
			ListCtrl.InsertItem(listNum, str, listNum);
		}

		vtkUnsignedCharArray *imageArray = GetDocument()->m_imageArray.GetAt(listNum);

		if (imageArray == NULL)
		{
			CBitmap bitmap;
			bitmap.LoadBitmap(IDB_BITMAP1);
			m_ImageList->Replace(listNum, &bitmap, NULL);
			bitmap.DeleteObject();

		}
		else
		{
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
				m_ImageList->Replace(listNum, CBitmap::FromHandle(image), NULL);
				//bitmap.DeleteObject();
				//delete image;
		

				pStream->Release();
			}
		}
	}
	ListCtrl.SetRedraw(TRUE);
	ListCtrl.Invalidate();
}

void CvtkListView::LoadThumbnail(int frameNum)
{
	int listNum = 0;
	if (frameNum < GetDocument()->frameCount)
		listNum = frameNum + 1;

	CListCtrl& ListCtrl = GetListCtrl();

	vtkUnsignedCharArray *imageArray = GetDocument()->m_imageArray.GetAt(listNum);

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
		m_ImageList->Replace(listNum, CBitmap::FromHandle(image), NULL);
		//bitmap.DeleteObject();
		//delete image;
		

		pStream->Release();
	}

	// Redraw only a current item for removing flickering and fast speed.
	ListCtrl.RedrawItems(listNum, listNum);
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


BOOL CvtkListView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	vtkSmartPointer<vtkNamedColors> namedColors = vtkSmartPointer<vtkNamedColors>::New();
	unsigned char *bgColor = namedColors->GetColor3ub("white_smoke").GetData();
	//namedColors->GetColor3d("white_smoke").GetData();

	// Set brush to desired background color.
	CBrush backBrush(RGB(bgColor[0], bgColor[1], bgColor[2]));
	// Save old brush.
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed.
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

    return TRUE; 
	//return CListView::OnEraseBkgnd(pDC);
}


void CvtkListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CvtkListView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int listNum = pNMItemActivate->iItem;
	std::cout << "list num : " << listNum << std::endl;

	CMDIFrameWnd * pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	ASSERT(pFrame != NULL);

	//pFrame->PostMessage(WM_THREADDONE, 0, 0);
	pFrame->PostMessage(WM_COMMAND, ID_VTK_PLANE, 0);
	std::cout << "PostMessage(WM_COMMAND, ID_VTK_PLANE)" << std::endl;
	//LRESULT ret = SendMessage(WM_COMMAND, ID_VTK_PLANE, 0);
	//std::cout << "SendMessage(WM_COMMAND, ID_VTK_PLANE) : " << ret << std::endl;
	
	GetDocument()->SelectItem(listNum);

	*pResult = 0;
}
