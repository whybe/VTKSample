
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


//#define LABID "asds"
#define LABNAME "201408092135"
//#define LABNAME "201408092137"

class CvtkDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CvtkDoc();
	DECLARE_DYNCREATE(CvtkDoc)

// 특성입니다.
public:
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

// 작업입니다.
public:

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
private:
	BOOL QueryData();
	void OffScreenRndering();
};
