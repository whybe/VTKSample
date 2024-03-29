
// CvtkPlaneView.cpp : CvtkPlaneView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif

#include "vtkDoc.h"
#include "vtkPlaneView.h"
#include "vtkMouseInteractorStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkPlaneView

IMPLEMENT_DYNCREATE(CvtkPlaneView, CView)

BEGIN_MESSAGE_MAP(CvtkPlaneView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkPlaneView 생성/소멸

CvtkPlaneView::CvtkPlaneView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	MFCWindow = NULL;
	renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
	selectedRenderer = vtkSmartPointer<vtkRenderer>::New();
	actor = vtkSmartPointer<vtkActor>::New();
	mouseInteractorStyle = vtkSmartPointer<vtkMouseInteractorStyle>::New();

	polyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	namedColors = vtkSmartPointer<vtkNamedColors>::New();
}

CvtkPlaneView::~CvtkPlaneView()
{
	if(NULL != MFCWindow)
		delete MFCWindow;
}

BOOL CvtkPlaneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CvtkPlaneView 그리기

void CvtkPlaneView::OnDraw(CDC* pDC)
{
	CvtkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if(NULL != MFCWindow && pDC->IsPrinting())
		MFCWindow->DrawDC(pDC);
}


// CvtkPlaneView 진단

#ifdef _DEBUG
void CvtkPlaneView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkPlaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkDoc* CvtkPlaneView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkPlaneView 메시지 처리기


void CvtkPlaneView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	renderer->SetLayer(0);
	selectedRenderer->SetActiveCamera(renderer->GetActiveCamera());
	selectedRenderer->SetLayer(1);

	MFCWindow = new vtkMFCWindow(this);
	MFCWindow->GetRenderWindow()->SetNumberOfLayers(2);
	MFCWindow->GetRenderWindow()->AddRenderer(renderer);
	MFCWindow->GetRenderWindow()->AddRenderer(selectedRenderer);
	//MFCWindow->GetRenderWindow()->SetSize(500,500);

	mouseInteractorStyle->selectedRenderer = selectedRenderer;
	mouseInteractorStyle->SetDefaultRenderer(renderer);

	renderWindowInteractor->SetInteractorStyle(mouseInteractorStyle);
	renderWindowInteractor->SetRenderWindow(MFCWindow->GetRenderWindow());
	renderWindowInteractor->Initialize();
	
	//renderer->ResetCamera();
	renderer->SetBackground(
		namedColors->GetColor3d("white_smoke").GetData());

	renderer->ResetCamera();
	vtkCamera *camera = renderer->GetActiveCamera();
	camera->ParallelProjectionOn();
	//vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	//double MotionFactor = style->GetMotionFactor();
	//double MouseWheelMotionFactor = style->GetMouseWheelMotionFactor();
	//double factor = MotionFactor * 0.2 * MouseWheelMotionFactor;
	//factor = pow(1.1, factor);
	//camera->SetParallelScale(camera->GetParallelScale() / factor / factor);
	camera->SetParallelScale(0.5);
	//camera->SetParallelScale(0.482963);
	std::cout << "parallel scale : " << camera->GetParallelScale() << std::endl;

	//if(NULL != GetDocument()->GetPlaneSource(0))
	//{
	//	// Create a mapper and actor
	//	polyDataMapper->SetInputData(
	//		GetDocument()->GetPlaneSource(0)->GetOutput());
	//	actor->SetMapper(polyDataMapper);
	//	
	//	mouseInteractorStyle->addressCount = GetDocument()->addressCount;
	//	mouseInteractorStyle->polyData = 
	//		GetDocument()->GetPlaneSource(0)->GetOutput();

	//	// renderer
	//	renderer->AddActor(actor);
	//}
}

BOOL CvtkPlaneView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CvtkPlaneView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(NULL != MFCWindow)
		MFCWindow->MoveWindow(0, 0, cx, cy);
}

void CvtkPlaneView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	std::cout << "OnUpate" << std::endl;

	if(NULL != GetDocument()->GetPlaneSource())
	{
		// Create a mapper and actor
		polyDataMapper->SetInputData(
			GetDocument()->GetPlaneSource()->GetOutput());
		actor->SetMapper(polyDataMapper);
		
		mouseInteractorStyle->addressCount = GetDocument()->addressCount;
		mouseInteractorStyle->polyData = 
			GetDocument()->GetPlaneSource()->GetOutput();

		// renderer
		renderer->AddActor(actor);
	}

	Invalidate();
}
