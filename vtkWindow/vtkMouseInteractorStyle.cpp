#include "StdAfx.h"
#include "vtkMouseInteractorStyle.h"

vtkStandardNewMacro(vtkMouseInteractorStyle);

vtkMouseInteractorStyle::vtkMouseInteractorStyle()
{
	polyData = NULL;
	selectedRenderer = NULL;
	selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    selectedActor = vtkSmartPointer<vtkActor>::New();
}

vtkMouseInteractorStyle::~vtkMouseInteractorStyle()
{
}

//void vtkMouseInteractorStyle::OnLeftButtonDown()
void vtkMouseInteractorStyle::OnMouseMove()
{
	if(selectedRenderer == NULL)
	{
		//selectedRenderer.TakeReference(this->GetDefaultRenderer());
		//selectedRenderer = vtkSmartPointer<vtkRenderer>::Take(this->GetDefaultRenderer());
		selectedRenderer = this->GetDefaultRenderer();
		//vtkActorCollection *actors = selectedRenderer->GetActors();
		//actors->InitTraversal();
		//for (int i = 0; i < actors->GetNumberOfItems(); ++i)
		//{
		//	
		//}
		//selectedRenderer->RemoveActor(selectedActor);
		//if (selectedRenderer->HasViewProp(selectedActor))
		//	selectedRenderer->RemoveViewProp(selectedActor);
	}
	//else
	//{
	//	selectedRenderer->RemoveAllViewProps();
	//}

	//selectedRenderer->RemoveActor(selectedActor);

	// Get the location of the click (in window coordinates)
	int* pos = this->GetInteractor()->GetEventPosition();

	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.0005);

	// Pick from this location.
	picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());
	std::cout << "Cell id is: " << picker->GetCellId() << std::endl;
	//double* worldPosition = picker->GetPickPosition();
	
	if(picker->GetCellId() == -1)
	{
		//this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(selectedActor);

		vtkPropCollection* props = selectedRenderer->GetViewProps(); //iterate through and set each visibility to 0
		props->InitTraversal();
		for(int i = 0; i < props->GetNumberOfItems(); i++)
		{
			props->GetNextProp()->VisibilityOff();
		}
		this->GetDefaultRenderer()->GetRenderWindow()->Render();
	}
	else
	{
		//std::cout << "Pick position is: " << worldPosition[0] << " " << worldPosition[1]
		//<< " " << worldPosition[2] << endl;

		vtkSmartPointer<vtkIdTypeArray> ids =
			vtkSmartPointer<vtkIdTypeArray>::New();
		ids->SetNumberOfComponents(1);
		ids->InsertNextValue(picker->GetCellId());

		vtkSmartPointer<vtkSelectionNode> selectionNode =
			vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(ids);

		vtkSmartPointer<vtkSelection> selection =
			vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		vtkSmartPointer<vtkExtractSelection> extractSelection =
			vtkSmartPointer<vtkExtractSelection>::New();
#if VTK_MAJOR_VERSION <= 5
		extractSelection->SetInput(0, this->Data);
		extractSelection->SetInput(1, selection);
#else
		extractSelection->SetInputData(0, this->polyData);
		extractSelection->SetInputData(1, selection);
#endif
		extractSelection->Update();

		// In selection
		vtkSmartPointer<vtkUnstructuredGrid> selected =
			vtkSmartPointer<vtkUnstructuredGrid>::New();
		selected->ShallowCopy(extractSelection->GetOutput());

		//std::cout << "There are " << selected->GetNumberOfPoints()
		//	<< " points in the selection." << std::endl;
		//std::cout << "There are " << selected->GetNumberOfCells()
		//	<< " cells in the selection." << std::endl;


#if VTK_MAJOR_VERSION <= 5
		selectedMapper->SetInputConnection(
			selected->GetProducerPort());
#else
		selectedMapper->SetInputData(selected);
#endif

		selectedActor->SetMapper(selectedMapper);
		selectedActor->GetProperty()->EdgeVisibilityOn();
		selectedActor->GetProperty()->SetEdgeColor(1,0,0);
		selectedActor->GetProperty()->SetLineWidth(0.5);

		selectedActor->VisibilityOn();

		//this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(selectedActor);
		selectedRenderer->AddActor(selectedActor);
		//this->GetDefaultRenderer()->GetRenderWindow()->Render();
	}

	//if(picker->GetCellId() != oldCellId)
	//{
	//	//this->GetCurrentRenderer()->Render();
	//	this->Interactor->GetRenderWindow()->Render();
	//}

	//std::cout << "this->Interactor->GetRenderWindow()->GetRenderers() : " << this->Interactor->GetRenderWindow()->GetRenderers()->GetNumberOfItems() << std::endl;
	
	//std::cout << "selectedRender->GetActors() : " << selectedRenderer->GetActors()->GetNumberOfItems() << std::endl;

	selectedRenderer->GetRenderWindow()->Render();

	// Forward events
	//vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	vtkInteractorStyleTrackballCamera::OnMouseMove();
}