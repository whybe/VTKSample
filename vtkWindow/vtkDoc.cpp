
// vtkWindowDoc.cpp : CvtkDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "vtkApp.h"
#endif

#include "vtkDoc.h"
#include "vtkUtil.h"
#include "MainFrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CvtkDoc

IMPLEMENT_DYNCREATE(CvtkDoc, CDocument)

BEGIN_MESSAGE_MAP(CvtkDoc, CDocument)
END_MESSAGE_MAP()


// CvtkDoc 생성/소멸

CvtkDoc::CvtkDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	errStatus = TRUE;
	errString = _T("");

	//labID = LABID;
	//labName = LABNAME;
	SetLabName(LABNAME);
	addressCount = 0;
	frameCount = 0;

	//updates = vtkSmartPointer<vtkIntArray>::New();
	updateTable = vtkSmartPointer<vtkTable>::New();
	planeSource = vtkSmartPointer<vtkPlaneSource>::New();

	//QueryData();
	if (OpenDB()) {
		SetAddressCountFromDB();
		SetFrameCountFromDB();
		InitializeUpdateTable();
		StartThread();
	}

	//xRes = 64;
	xRes = 128;
	yRes = 1;

	OffScreenRndering();
}

CvtkDoc::~CvtkDoc()
{
	if (m_pThread)
		StopThread();
}

BOOL CvtkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	if(!errStatus)
	{
		AfxMessageBox(errString, NULL, MB_ICONERROR);
		return FALSE;
	}

	UpdatePlaneSource();

	return TRUE;
}

void CvtkDoc::UpdatePlaneSource()
{
#ifdef CHECK_TIME
	float Time;
	BOOL err;
	CHECK_TIME_START;
#endif

	yRes = addressCount/xRes + 1;
	int tableSize = xRes*yRes;

	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();

	//planeSource = vtkSmartPointer<vtkPlaneSource>::New();
	//planeSource->SetCenter(1.0, 0.0, 0.0);
	//planeSource->SetNormal(1.0, 0.0, 1.0);
	planeSource->SetXResolution(xRes);
	planeSource->SetYResolution(yRes);
	planeSource->Update();

	//MakeLUTFromCTF(tableSize, lut, addressCount, updates);
	vtkUtil::MakeLUTFromCTF(tableSize, lut, addressCount, vtkIntArray::SafeDownCast(updateTable->GetColumnByName("Total")), 0, frameCount);
	//vtkUtil::MakeLUTFromCTF(tableSize, lut, addressCount, vtkIntArray::SafeDownCast(updateTable->GetColumnByName("Frame1")), 0, 1);

	vtkSmartPointer<vtkUnsignedCharArray> colorData = 
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	colorData->SetName("colors");
	colorData->SetNumberOfComponents(3);
	std::cout 
		<< "Using a lookup table created from a color transfer function."
		<< std::endl;
	vtkUtil::MakeCellData(tableSize, lut, colorData);
	planeSource->GetOutput()->GetCellData()->SetScalars(colorData);
	planeSource->GetOutput()->GetCellData()->AddArray(updateTable->GetColumnByName("Address"));
	planeSource->GetOutput()->GetCellData()->AddArray(updateTable->GetColumnByName("Total"));

#ifdef CHECK_TIME
	CHECK_TIME_END(Time, err);
	//if(err) _tprintf(_T("create Plane : %8.6f ms\n"), Time);
	std::cout << "create planeSource[" << xRes << "][" << yRes << "] : " << Time << " ms" << std::endl;
#endif
}


// CvtkDoc serialization

void CvtkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CvtkDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CvtkDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CvtkDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CvtkDoc 진단

#ifdef _DEBUG
void CvtkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvtkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

BOOL CvtkDoc::OpenDB()
{
	//mysql db open & get query Instance
	db = vtkSmartPointer<vtkMySQLDatabase>::Take(vtkMySQLDatabase::SafeDownCast(
		vtkMySQLDatabase::CreateFromURL("mysql://root:winter09@localhost/dumpreceiver")
		));
	// url syntax:
	// mysql://'[[username[':'password]'@']hostname[':'port]]'/'[dbname]
	bool status = db->Open();
	//std::cout << "Database open? " << status << std::endl;
	if(!status)
	{
		errStatus = FALSE;
		errString = _T("MySQL DB Open Fail");
		return FALSE;
	}
	query = vtkSmartPointer<vtkSQLQuery>::Take(db->GetQueryInstance());

	return TRUE;
}

void CvtkDoc::SetLabName(vtkStdString labName)
{
	this->labName = labName;

	std::cout << "labName : " << labName << std::endl;
}

void CvtkDoc::SetAddressCountFromDB()
{
	vtkStdString queryStr = 
		"select count(dumpdata.Frame) from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' group by dumpdata.Frame LIMIT 1";
	query->SetQuery(queryStr);
	query->Execute();
	query->NextRow();
	addressCount = query->DataValue(0).ToUnsignedInt();

	std::cout << "addressCount : " << addressCount << std::endl;
}

void CvtkDoc::SetFrameCountFromDB()
{
	vtkStdString queryStr = 
		"select count(dumpdata.Address) from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' group by dumpdata.Address LIMIT 1";
	query->SetQuery(queryStr);
	query->Execute();
	query->NextRow();
	frameCount = query->DataValue(0).ToUnsignedInt();

	std::cout << "frameCount : " << frameCount << std::endl;
}

void CvtkDoc::InitializeUpdateTable()
{
	vtkSmartPointer<vtkIntArray> sumOfUpdateds = vtkSmartPointer<vtkIntArray>::New();
	sumOfUpdateds->SetNumberOfComponents(1);
	sumOfUpdateds->SetNumberOfValues(addressCount);
	sumOfUpdateds->SetName("Total");
	updateTable->AddColumn(sumOfUpdateds);

	vtkSmartPointer<vtkIntArray> sections = vtkSmartPointer<vtkIntArray>::New();
	sections->SetNumberOfComponents(1);
	sections->SetNumberOfValues(addressCount);
	sections->SetName("Section");
	updateTable->AddColumn(sections);
	
	vtkSmartPointer<vtkIntArray> addresses = vtkSmartPointer<vtkIntArray>::New();
	addresses->SetNumberOfComponents(1);
	addresses->SetNumberOfValues(addressCount);
	addresses->SetName("Address");
	updateTable->AddColumn(addresses);

	std::cout << "rows : " << updateTable->GetNumberOfRows() << ", cols : " << updateTable->GetNumberOfColumns() << std::endl;
	std::cout << "size of updateTable : " << updateTable->GetActualMemorySize() << " kb" << std::endl;
}

void CvtkDoc::SetUpdateTableFromDB()
{
#ifdef CHECK_TIME
	float Time;
	BOOL err;
	CHECK_TIME_START;
#endif

	vtkStdString queryStr = 
		//"select dumpdata.Address, dumpdata.Frame, dumpdata.Value, dumpdata.Updated+0, dumpdata.Section from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' order by Address, Frame";
		"select dumpdata.Address, dumpdata.Frame, dumpdata.Updated+0, dumpdata.Section from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' order by Address, Frame";
	query->SetQuery(queryStr);
	query->Execute();

	bool ret;
	for(int addressNum = 0; addressNum < addressCount; addressNum++)
	{
		vtkVariant Address;
		vtkVariant Frame;
		//vtkVariant Value;
		vtkVariant Updated;
		vtkVariant Section;

		int updateCount = 0;
		for(int frameNum = 0; frameNum < frameCount; frameNum++)
		{
			ret = query->NextRow();
			if(!ret)
			{
				break;
			}

			Address = query->DataValue(0);
			Frame = query->DataValue(1);
			Updated = query->DataValue(2);
			Section = query->DataValue(3);

			//Value = query->DataValue(2);
			//vtkStdString valueName = "Value" + std::to_string((_ULonglong)frameNum);
			//updateTable->SetValueByName(addressNum, valueName, Value);
			//Updated = query->DataValue(3);
			//vtkStdString updatedName = "Updated" + std::to_string((_ULonglong)frameNum);
			//updateTable->SetValueByName(addressNum, updatedName, Updated.ToInt());
			//Section = query->DataValue(4);

			if (frameNum == 0 && addressNum == 0)
			{
				std::cout << "type of Address : " << Address.GetTypeAsString() << std::endl;
				std::cout << "type of Frame : " << Frame.GetTypeAsString() << std::endl;
				//std::cout << "type of Value : " << Value.GetTypeAsString() << std::endl;
				std::cout << "type of Updated : " << Updated.GetTypeAsString() << std::endl;
				std::cout << "type of Section : " << Section.GetTypeAsString() << std::endl;
			}

			updateCount += Updated.ToInt();

			if(frameNum != Frame.ToInt())
			{
				std::cout << "frameNum error : " << frameNum << ", " << Frame.ToInt() << std::endl;
				ret = false;
				break;
			}
		}

		if(!ret)
		{
			break;
		}

		//if(addressNum != Address.ToInt())
		//{
		//	std::cout << "addressNum error : " << addressNum << ", " << Address.ToInt() << std::endl;
		//	break;
		//}

		//updates->SetValue(addressNum, updateCount);
		updateTable->SetValueByName(addressNum, "Total", updateCount);
		updateTable->SetValueByName(addressNum, "Section", Section);
		updateTable->SetValueByName(addressNum, "Address", Address);
	}

#ifdef CHECK_TIME
	CHECK_TIME_END(Time, err);
	if(err)
		std::cout << "Create updateTable : " << Time << " ms" << std::endl;
#endif

	//updateTable->Dump();
}

UINT CvtkDoc::ThreadFunc(LPVOID pThreadParam)
{
	THREADPARAM *pParam = (THREADPARAM *)pThreadParam;

	CvtkDoc *pCvtkDoc = (CvtkDoc *)pParam->pWnd;
	delete pParam;

	// TODO
	pCvtkDoc->SetUpdateTableFromDB();

	CMDIFrameWnd * pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	ASSERT(pFrame);

	pFrame->PostMessage(WM_THREADDONE, 0, 0);
	std::cout << "PostMessage(WM_THREADDONE)" << std::endl;

	//LRESULT ret;
	//ret = pFrame->SendMessage(WM_THREADDONE, 0, 0);
	//std::cout << "SendMessage(WM_THREADDONE) : " << ret << std::endl;
	
	//ret = pView->SendMessage(WM_VTKRENDER, 0, 0);
	//std::cout << "SendMessage(WM_THREADDONE) : " << ret << std::endl;

	//AfxEndThread(0);
	return 0;
}

void CvtkDoc::StartThread()
{
	THREADPARAM *pThreadParam = new THREADPARAM;
	pThreadParam->pWnd = (CWnd *)this;

	m_pThread = AfxBeginThread(ThreadFunc, pThreadParam);
}

void CvtkDoc::StopThread()
{
	Sleep(100);

	if (::WaitForSingleObject(m_pThread->m_hThread, INFINITE))
	{
		m_pThread = NULL;

		// TODO
	}
}

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkGraphicsFactory.h>

void CvtkDoc::OffScreenRndering()
{
#ifdef CHECK_TIME
	float Time;
	BOOL err;
	CHECK_TIME_START;
#endif
	//sphere 1
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());


    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // a renderer and render window
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetOffScreenRendering(1);
    renderWindow->AddRenderer(renderer);

    // add the actors to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(1, 1, 1); // Background color white

	renderer->ResetCamera();

	vtkCamera *camera = renderer->GetActiveCamera();
	camera->ParallelProjectionOn();
	camera->SetParallelScale(0.5);

    renderWindow->Render();

    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
        vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow);
    windowToImageFilter->Update();

    vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("sphere.png");
    writer->SetInputConnection(windowToImageFilter->GetOutputPort());
    writer->Write();

#ifdef CHECK_TIME
	CHECK_TIME_END(Time, err);
	if(err)
		std::cout << "OffScreenRndering : " << Time << " ms" << std::endl;
#endif
}

//BOOL CvtkDoc::QueryData()
//{
//	// variables
//
//	//mysql db open & get query Instance
//	vtkSmartPointer<vtkMySQLDatabase> db = 
//		vtkSmartPointer<vtkMySQLDatabase>::Take(vtkMySQLDatabase::SafeDownCast(
//			//vtkMySQLDatabase::CreateFromURL("mysql://root:winter09@localhost/vtk")
//			vtkMySQLDatabase::CreateFromURL("mysql://root:winter09@localhost/dumpreceiver")
//		));
//	// url syntax:
//	// mysql://'[[username[':'password]'@']hostname[':'port]]'/'[dbname]
//	bool status = db->Open();
//	//std::cout << "Database open? " << status << std::endl;
//	if(!status)
//	{
//		errStatus = FALSE;
//		errString = _T("MySQL DB Open Fail");
//		return FALSE;
//	}
//	vtkSmartPointer<vtkSQLQuery> query = vtkSmartPointer<vtkSQLQuery>::Take(db->GetQueryInstance());
//
//	// labID
//	//vtkStdString labID = LABID;
//	//labID = LABID;
//	//_tprintf(_T("labID : %s\n"), CString(labID));
//	std::cout << "labName : " << labName << std::endl;
//
//	// query string variable
//	vtkStdString queryStr;
//
//	// address count
//	//int addressCount;
//	queryStr = 
//		//"select count(*) from vtk.dumped_data where LABID = '" + labID + "' group by Frame";
//		"select count(dumpdata.Frame) from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' group by dumpdata.Frame LIMIT 1";
//	query->SetQuery(queryStr);
//	//_tprintf(_T("%s\n"), CString(query->GetQuery()));
//	query->Execute();
//	query->NextRow();
//	addressCount = query->DataValue(0).ToUnsignedInt();
//	//_tprintf(_T("addressCount : %d\n"), addressCount);
//	std::cout << "addressCount : " << addressCount << std::endl;
//
//	// frame count
//	//int frameCount;
//	queryStr = 
//		//"select count(*) from vtk.dumped_data where LABID = '" + labID + "' group by Address";
//		"select count(dumpdata.Address) from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' group by dumpdata.Address LIMIT 1";
//	query->SetQuery(queryStr);
//	//_tprintf(_T("%s\n"), CString(query->GetQuery()));
//	query->Execute();
//	query->NextRow();
//	frameCount = query->DataValue(0).ToUnsignedInt();
//	//_tprintf(_T("frameCount : %d\n"), frameCount);
//	std::cout << "frameCount : " << frameCount << std::endl;
//
//#ifdef CHECK_TIME
//	float Time;
//	BOOL err;
//	CHECK_TIME_START;
//#endif
//
//	// generate update array
//	//CArray<int, int> updateArr;
//	//updateArr.SetSize(addressCount);
//	//updates = vtkSmartPointer<vtkIntArray>::New();
//	//updates->SetNumberOfComponents(1);
//	//updates->SetNumberOfValues(addressCount);
//	//updates->SetName("Updates");
//
//	//for (int i = 0; i < frameCount; ++i)
//	//{
//	//	vtkSmartPointer<vtkIntArray> updateds = vtkSmartPointer<vtkIntArray>::New();
//	//	updateds->SetNumberOfComponents(1);
//	//	updateds->SetNumberOfValues(addressCount);
//	//	vtkStdString str = "Updated" + std::to_string((_ULonglong)i);
//	//	//std::cout << str << std::endl;
//	//	updateds->SetName(str);
//	//	updateTable->AddColumn(updateds);
//	//}
//
//	//for (int i = 0; i < frameCount; ++i)
//	//{
//	//	vtkSmartPointer<vtkIntArray> values = vtkSmartPointer<vtkIntArray>::New();
//	//	values->SetNumberOfComponents(1);
//	//	values->SetNumberOfValues(addressCount);
//	//	vtkStdString str = "Value" + std::to_string((_ULonglong)i);
//	//	//std::cout << str << std::endl;
//	//	values->SetName(str);
//	//	updateTable->AddColumn(values);
//	//}
//
//	vtkSmartPointer<vtkIntArray> sumOfUpdateds = vtkSmartPointer<vtkIntArray>::New();
//	sumOfUpdateds->SetNumberOfComponents(1);
//	sumOfUpdateds->SetNumberOfValues(addressCount);
//	sumOfUpdateds->SetName("Total");
//	updateTable->AddColumn(sumOfUpdateds);
//
//	vtkSmartPointer<vtkIntArray> sections = vtkSmartPointer<vtkIntArray>::New();
//	sections->SetNumberOfComponents(1);
//	sections->SetNumberOfValues(addressCount);
//	sections->SetName("Section");
//	updateTable->AddColumn(sections);
//	
//	vtkSmartPointer<vtkIntArray> addresses = vtkSmartPointer<vtkIntArray>::New();
//	addresses->SetNumberOfComponents(1);
//	addresses->SetNumberOfValues(addressCount);
//	addresses->SetName("Address");
//	updateTable->AddColumn(addresses);
//
//	queryStr = 
//		//"select Address, Frame, Value from vtk.dumped_data where LABID = '" + labID + "' order by Address, Frame;";
//		//"select dumpdata.Address, dumpdata.Frame, dumpdata.Value, dumpdata.Updated+0, dumpdata.Section from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' order by Address, Frame";
//		"select dumpdata.Address, dumpdata.Frame, dumpdata.Updated+0, dumpdata.Section from labname, dumpdata where labname.ID = dumpdata.LABID and labname.LabName = '" + labName + "' order by Address, Frame";
//	query->SetQuery(queryStr);
//	//_tprintf(_T("%s\n"), CString(query->GetQuery()));
//	query->Execute();
//
//	bool ret;
//	for(int addressNum = 0; addressNum < addressCount; addressNum++)
//	{
//		vtkVariant Address;
//		vtkVariant Frame;
//		//vtkVariant Value;
//		vtkVariant Updated;
//		vtkVariant Section;
//
//		//int oldValue = -1;
//		//int newValue = -1;
//		int updateCount = 0;
//		for(int frameNum = 0; frameNum < frameCount; frameNum++)
//		{
//			ret = query->NextRow();
//			if(!ret)
//			{
//				break;
//			}
//
//			Address = query->DataValue(0);
//			Frame = query->DataValue(1);
//			Updated = query->DataValue(2);
//			Section = query->DataValue(3);
//
//			//Value = query->DataValue(2);
//			//vtkStdString valueName = "Value" + std::to_string((_ULonglong)frameNum);
//			//updateTable->SetValueByName(addressNum, valueName, Value);
//			//Updated = query->DataValue(3);
//			//vtkStdString updatedName = "Updated" + std::to_string((_ULonglong)frameNum);
//			//updateTable->SetValueByName(addressNum, updatedName, Updated.ToInt());
//			//Section = query->DataValue(4);
//
//			if (frameNum == 0 && addressNum == 0)
//			{
//				std::cout << "type of Address : " << Address.GetTypeAsString() << std::endl;
//				std::cout << "type of Frame : " << Frame.GetTypeAsString() << std::endl;
//				//std::cout << "type of Value : " << Value.GetTypeAsString() << std::endl;
//				std::cout << "type of Updated : " << Updated.GetTypeAsString() << std::endl;
//				std::cout << "type of Section : " << Section.GetTypeAsString() << std::endl;
//			}
//
//			//if (Updated.IsInt())
//			//	std::cout << "Updated : " << Updated.ToInt() << std::endl;
//
//			updateCount += Updated.ToInt();
//
//			if(frameNum != Frame.ToInt())
//			{
//				//_tprintf(_T("frameNum error : %d, %d\n"), frameNum, Frame.ToInt());
//				std::cout << "frameNum error : " << frameNum << ", " << Frame.ToInt() << std::endl;
//				ret = false;
//				break;
//			}
//
//			//newValue = (int)strtol(Value.ToString().c_str(), NULL, 16);
//			//if(!(oldValue < 0) && oldValue != newValue)
//			//{
//			//	updateCount += 1;
//			//}
//
//			//oldValue = newValue;
//		}
//
//		if(!ret)
//		{
//			break;
//		}
//
//		//_tprintf(_T("%s\n"), CString(Address.ToString().c_str()));
//		//if(addressNum != (int)strtol(Address.ToString().c_str(), NULL, 16))
//		//if(addressNum != Address.ToInt())
//		//{
//		//	//_tprintf(_T("addressNum error : %d, %s\n"), addressNum, CString(Address.ToString().c_str()));
//		//	std::cout << "addressNum error : " << addressNum << ", " << Address.ToInt() << std::endl;
//		//	break;
//		//}
//
//		//_tprintf(_T("%d "), updateCount);
//		//std::cout << "updates[" << Address << "] : " << updateCount << std::endl;
//		//updateArr.SetAt(addressNum, updateCount);
//		//updates->SetValue(addressNum, updateCount);
//		updateTable->SetValueByName(addressNum, "Total", updateCount);
//		updateTable->SetValueByName(addressNum, "Section", Section);
//		updateTable->SetValueByName(addressNum, "Address", Address);
//	}
//
//#ifdef CHECK_TIME
//	CHECK_TIME_END(Time, err);
//	if(err) 
//		//_tprintf(_T("create Array updates[%d] : %8.6f ms\n"), addressCount, Time);
//		//std::cout << "create Array updates[" << addressCount << "] : " << Time << " ms" << std::endl;
//		std::cout << "create Table updateTable[" << updateTable->GetNumberOfRows() << "][" << updateTable->GetNumberOfColumns() << "] : " << Time << " ms" << std::endl;
//#endif
//
//	//std::cout << "rows : " << updateTable->GetNumberOfRows() << ", cols : " << updateTable->GetNumberOfColumns() << std::endl;
//
//	std::cout << "size of updateTable : " << updateTable->GetActualMemorySize() << " kb" << std::endl;
//
//
//	//updateTable->Dump();
//
//	//for(int addressNum = 0; addressNum < addressCount; addressNum++)
//	//{
//	//	//_tprintf(_T("%d "), updateArr.GetAt(addressNum));
//	//	_tprintf(_T("%d "), updates->GetValue(addressNum));
//	//}
//
//	return TRUE;
//}
