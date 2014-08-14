// vtkMFCDocument.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "vtkApp.h"
#include "vtkMFCDocument.h"


// vtkMFCDocument

IMPLEMENT_DYNCREATE(vtkMFCDocument, CDocument)

vtkMFCDocument::vtkMFCDocument()
{
	this->Props = vtkSmartPointer<vtkPropCollection>::New();
}

BOOL vtkMFCDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

vtkMFCDocument::~vtkMFCDocument()
{
}


BEGIN_MESSAGE_MAP(vtkMFCDocument, CDocument)
END_MESSAGE_MAP()


// vtkMFCDocument �����Դϴ�.

#ifdef _DEBUG
void vtkMFCDocument::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void vtkMFCDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// vtkMFCDocument serialization�Դϴ�.

void vtkMFCDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}
#endif


// vtkMFCDocument ����Դϴ�.
