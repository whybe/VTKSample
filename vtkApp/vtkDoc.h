
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

#define THUMBNAIL_WIDTH 300
#define THUMBNAIL_HEIGHT 300

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
	int tableSize;

	bool m_bDo;
	CWinThread *m_pThread;

	//CImageList m_thumbnailList;
	//CArray<vtkSmartPointer<vtkUnsignedCharArray>, vtkSmartPointer<vtkUnsignedCharArray>> m_imageArray;
	CArray<vtkUnsignedCharArray*, vtkUnsignedCharArray*> m_imageArray;

// �۾��Դϴ�.
private:
	BOOL OpenDB();
	void SetLabName(vtkStdString labName);
	void SetAddressCountFromDB();
	void SetFrameCountFromDB();
	void InitializeUpdateTable();
	void SetUpdateTableFromDB();
	//BOOL QueryData();

public:
	static UINT ThreadFunc(LPVOID pThreadParam);
	void StartThread(UINT (*fn)(LPVOID));
	void StopThread();
	void UpdatePlaneSource();

	void OffScreenRendering();
	void OffScreenRendering(int frameNum);
	static UINT OffScreenRenderingThreadFunc(LPVOID pThreadParam);
	CView* CvtkDoc::GetView(CRuntimeClass* pClass);

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
