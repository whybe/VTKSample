#pragma once

// vtkMFCDocument �����Դϴ�.

#include <vtkSmartPointer.h>
#include <vtkPropCollection.h>

class vtkMFCDocument : public CDocument
{
	DECLARE_DYNCREATE(vtkMFCDocument)

protected:
	vtkSmartPointer<vtkPropCollection> Props;

public:
	vtkPropCollection *GetViewProps() {return this->Props.GetPointer();};

public:
	vtkMFCDocument();
	virtual ~vtkMFCDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // ���� ��/����� ���� �����ǵǾ����ϴ�.
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
