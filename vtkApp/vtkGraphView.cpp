
// CvtkGraphView.cpp : CvtkGraphView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif

#include "vtkDoc.h"
#include "vtkGraphView.h"
#include "vtkMouseInteractorStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkGraphView

IMPLEMENT_DYNCREATE(CvtkGraphView, CView)

BEGIN_MESSAGE_MAP(CvtkGraphView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkGraphView 생성/소멸

CvtkGraphView::CvtkGraphView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	MFCWindow = NULL;
	//Renderer = vtkSmartPointer<vtkRenderer>::New();
	//Actor = vtkSmartPointer<vtkActor>::New();
	//PolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	//NamedColors = vtkSmartPointer<vtkNamedColors>::New();
	planeSource = vtkSmartPointer<vtkPlaneSource>::New();
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	actor = vtkSmartPointer<vtkActor>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	style = vtkSmartPointer<vtkMouseInteractorStyle>::New();
}

CvtkGraphView::~CvtkGraphView()
{
	if(NULL != MFCWindow)
		delete MFCWindow;
}

BOOL CvtkGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CvtkGraphView 그리기

void CvtkGraphView::OnDraw(CDC* pDC)
{
	CvtkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if(NULL != MFCWindow && pDC->IsPrinting())
		MFCWindow->DrawDC(pDC);
}


// CvtkGraphView 진단

#ifdef _DEBUG
void CvtkGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkDoc* CvtkGraphView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkGraphView 메시지 처리기


void CvtkGraphView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//MFCWindow = new vtkMFCWindow(this);
	//MFCWindow->GetRenderWindow()->AddRenderer(Renderer);
	//Renderer->SetBackground(NamedColors->GetColor3d("white_smoke").GetData());

	//if(NULL != GetDocument()->PlaneSource)
	//{
	//	vtkSmartPointer<vtkPlaneSource> planeSource =
	//		vtkSmartPointer<vtkPlaneSource>::New();
	//	planeSource->SetCenter(1.0, 0.0, 0.0);
	//	planeSource->SetNormal(1.0, 0.0, 1.0);
	//	planeSource->Update();

	//	vtkPolyData* plane = planeSource->GetOutput();

	//	//vtkPolyData* plane = GetDocument()->PlaneSource->GetOutput();

	//	// Create a mapper and actor
	//	PolyDataMapper->SetInputData(plane);
	//	Actor->SetMapper(PolyDataMapper);

	//	// renderer
	//	Renderer->AddActor(Actor);
	//}

	int resolution = 3;

	planeSource->SetXResolution(resolution);
	planeSource->SetYResolution(resolution);
	planeSource->Update();

	//vtkSmartPointer<vtkTriangleFilter> triangleFilter =
	//	vtkSmartPointer<vtkTriangleFilter>::New();
	//triangleFilter->SetInputConnection(planeSource->GetOutputPort());
	//triangleFilter->Update();

	//mapper->SetInputConnection(triangleFilter->GetOutputPort());
	mapper->SetInputConnection(planeSource->GetOutputPort());

	actor->GetProperty()->SetColor(0,1,0); //green
	actor->SetMapper(mapper);

	//vtkSmartPointer<vtkRenderWindow> renderWindow =
	//	vtkSmartPointer<vtkRenderWindow>::New();
	//renderWindow->AddRenderer(renderer);
	MFCWindow = new vtkMFCWindow(this);
	MFCWindow->GetRenderWindow()->AddRenderer(renderer);

	//renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->SetRenderWindow(MFCWindow->GetRenderWindow());
	renderWindowInteractor->Initialize();

	// Set the custom stype to use for interaction.
	style->SetDefaultRenderer(renderer);
	//style->Data = triangleFilter->GetOutput();
	style->polyData = planeSource->GetOutput();

	renderWindowInteractor->SetInteractorStyle(style);

	renderer->AddActor(actor);
	renderer->ResetCamera();

	renderer->SetBackground(0,0,1); // Blue

	//renderWindow->Render();
	//renderWindowInteractor->Start();
}


BOOL CvtkGraphView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CvtkGraphView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(NULL != MFCWindow)
		MFCWindow->MoveWindow(0, 0, cx, cy);
}
