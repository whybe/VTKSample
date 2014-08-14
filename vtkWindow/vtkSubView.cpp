
// CvtkSubView.cpp : CvtkSubView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif

#include "vtkDoc.h"
#include "vtkSubView.h"
//#include "vtkMouseInteractorStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkSubView

IMPLEMENT_DYNCREATE(CvtkSubView, CView)

BEGIN_MESSAGE_MAP(CvtkSubView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkSubView ����/�Ҹ�

CvtkSubView::CvtkSubView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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

CvtkSubView::~CvtkSubView()
{
	if(NULL != MFCWindow)
		delete MFCWindow;
}

BOOL CvtkSubView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CvtkSubView �׸���

void CvtkSubView::OnDraw(CDC* pDC)
{
	CvtkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if(NULL != MFCWindow && pDC->IsPrinting())
		MFCWindow->DrawDC(pDC);
}


// CvtkSubView ����

#ifdef _DEBUG
void CvtkSubView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkSubView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkDoc* CvtkSubView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkSubView �޽��� ó����


void CvtkSubView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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


BOOL CvtkSubView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CvtkSubView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(NULL != MFCWindow)
		MFCWindow->MoveWindow(0, 0, cx, cy);
}
