
// CvtkDoc.h : CvtkDoc 클래스의 인터페이스
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
#include <vtkNamedColors.h>
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
protected: // serialization에서만 만들어집니다.
	CvtkDoc();
	DECLARE_DYNCREATE(CvtkDoc)

// 특성입니다.
protected:
	vtkSmartPointer<vtkPlaneSource> planeSource;

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
	
	int xRes;
	int yRes;
	int tableSize;

	bool m_bDo;
	CWinThread *m_pThread;

	int m_listNum;

	//CImageList m_thumbnailList;
	CArray<vtkSmartPointer<vtkUnsignedCharArray>, vtkSmartPointer<vtkUnsignedCharArray>> m_imageArray;
	//CArray<vtkUnsignedCharArray*, vtkUnsignedCharArray*> m_imageArray;

	CArray<vtkSmartPointer<vtkPlaneSource>, vtkSmartPointer<vtkPlaneSource>> m_planeSourceArray;

// 작업입니다.
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

	vtkPlaneSource *GetPlaneSource(int listNum);
	vtkPlaneSource *GetPlaneSource();

	void SelectItem(int listNum);

	void OffScreenRendering();
	void OffScreenRendering(int frameNum);
	void OffScreenRenderingQuery(int frameNum);
	void OffScreenRenderingPlane();
	static UINT OffScreenRenderingThreadFunc(LPVOID pThreadParam);
	CView* CvtkDoc::GetView(CRuntimeClass* pClass);

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CvtkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
