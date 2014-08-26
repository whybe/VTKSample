
// CvtkMainView.cpp : CvtkMainView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif

#include "vtkDoc.h"
#include "vtkMainView.h"
//#include "vtkMouseInteractorStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvtkMainView

IMPLEMENT_DYNCREATE(CvtkMainView, CView)

BEGIN_MESSAGE_MAP(CvtkMainView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkMainView ����/�Ҹ�

CvtkMainView::CvtkMainView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	MFCWindow = NULL;
	renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
	selectedRenderer = vtkSmartPointer<vtkRenderer>::New();
	actor = vtkSmartPointer<vtkActor>::New();
	mouseInteractorStyle = vtkSmartPointer<vtkMouseInteractorStyle>::New();

	polyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	namedColors = vtkSmartPointer<vtkNamedColors>::New();
}

CvtkMainView::~CvtkMainView()
{
	if(NULL != MFCWindow)
		delete MFCWindow;
}

BOOL CvtkMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CvtkMainView �׸���

void CvtkMainView::OnDraw(CDC* pDC)
{
	CvtkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if(NULL != MFCWindow && pDC->IsPrinting())
		MFCWindow->DrawDC(pDC);
}


// CvtkMainView ����

#ifdef _DEBUG
void CvtkMainView::AssertValid() const
{
	CView::AssertValid();
}

void CvtkMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvtkDoc* CvtkMainView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvtkDoc)));
	return (CvtkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvtkMainView �޽��� ó����


void CvtkMainView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

	if(NULL != GetDocument()->planeSource)
	{
		// Create a mapper and actor
		polyDataMapper->SetInputData(
			GetDocument()->planeSource->GetOutput());
		actor->SetMapper(polyDataMapper);
		
		mouseInteractorStyle->addressCount = GetDocument()->addressCount;
		mouseInteractorStyle->polyData = 
			GetDocument()->planeSource->GetOutput();

		// renderer
		renderer->AddActor(actor);
	}
}

BOOL CvtkMainView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CvtkMainView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(NULL != MFCWindow)
		MFCWindow->MoveWindow(0, 0, cx, cy);
}