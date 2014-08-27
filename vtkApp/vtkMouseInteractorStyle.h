#pragma once
#include <vtkinteractorstyletrackballcamera.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkCellPicker.h>
#include <vtkType.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkCellData.h>
#include <vtkStdString.h>

class vtkMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static vtkMouseInteractorStyle* New();

public:
	//It was not necessary to use a smart pointer 
	//because we did not actually create any new objects. 

	vtkPolyData *polyData;
	vtkRenderer *selectedRenderer;

	int addressCount;

    vtkSmartPointer<vtkDataSetMapper> selectedMapper;
    vtkSmartPointer<vtkActor> selectedActor;
	vtkSmartPointer<vtkTextActor> textActor;

public:
	vtkMouseInteractorStyle();
	~vtkMouseInteractorStyle();

	//virtual void OnLeftButtonDown();
	virtual void OnMouseMove();
};

