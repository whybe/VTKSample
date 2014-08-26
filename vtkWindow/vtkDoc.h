
// CvtkDoc.h : CvtkDoc Ŭ������ �������̽�
//


#pragma once

#include <vtkSmartPointer.h>
#include <vtkPlaneSource.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>
#include <vtkTable.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>

#include <vtkCamera.h>

//#define LABID "asds"
#define LABNAME "201408092135"
//#define LABNAME "201408092137"

typedef struct tagThreadParam
{
	CWnd *pWnd;
} THREADPARAM;

class CvtkDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CvtkDoc();
	DECLARE_DYNCREATE(CvtkDoc)

// Ư���Դϴ�.
public:
	vtkSmartPointer<vtkMySQLDatabase> db;
	vtkSmartPointer<vtkSQLQuery> query;

	BOOL errStatus;
	CString errString;

	//vtkStdString labID;
	vtkStdString labName;
	int addressCount;
	int frameCount;

	//vtkSmartPointer<vtkIntArray> updates;
	vtkSmartPointer<vtkTable> updateTable;
	vtkSmartPointer<vtkPlaneSource> planeSource;
	
	int xRes;
	int yRes;

	CWinThread *m_pThread;

// �۾��Դϴ�.
private:
	BOOL OpenDB();
	void SetLabName(vtkStdString labName);
	void SetAddressCountFromDB();
	void SetFrameCountFromDB();
	void InitializeUpdateTable();
	void SetUpdateTableFromDB();
	//BOOL QueryData();
	void OffScreenRndering();

public:
	static UINT ThreadFunc(LPVOID pThreadParam);
	void StartThread();
	void StopThread();
	void UpdatePlaneSource();

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CvtkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
