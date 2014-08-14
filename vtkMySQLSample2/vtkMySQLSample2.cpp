// vtkMySQLSample2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "vtkMySQLSample2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 오류 코드를 필요에 따라 수정합니다.
			_tprintf(_T("심각한 오류: MFC를 초기화하지 못했습니다.\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 응용 프로그램의 동작은 여기에서 코딩합니다.

			// variables

			//mysql db open & get query Instance
			vtkSmartPointer<vtkMySQLDatabase> db = vtkSmartPointer<vtkMySQLDatabase>::Take(vtkMySQLDatabase::SafeDownCast(
					vtkMySQLDatabase::CreateFromURL("mysql://root:winter09@localhost/vtk")));
					// url syntax:
					// mysql://'[[username[':'password]'@']hostname[':'port]]'/'[dbname]
			bool status = db->Open();
			//std::cout << "Database open? " << status << std::endl;
			if(!status)
			{
				return EXIT_FAILURE;
			}
			vtkSmartPointer<vtkSQLQuery> query = vtkSmartPointer<vtkSQLQuery>::Take(db->GetQueryInstance());

			// labID
			vtkStdString labID = LABID;
			
			// query string variable
			vtkStdString queryStr;

			// address count
			int addressCount;
			queryStr = "select count(*) from vtk.dumped_data where LABID = '" + labID + "' group by Frame";
			query->SetQuery(queryStr);
			//_tprintf(_T("%s\n"), CString(query->GetQuery()));
			query->Execute();
			query->NextRow();
			addressCount = query->DataValue(0).ToUnsignedInt();
			_tprintf(_T("addressCount : %d\n"), addressCount);

			// frame count
			int frameCount;
			queryStr = "select count(*) from vtk.dumped_data where LABID = '" + labID + "' group by Address";
			query->SetQuery(queryStr);
			//_tprintf(_T("%s\n"), CString(query->GetQuery()));
			query->Execute();
			query->NextRow();
			frameCount = query->DataValue(0).ToUnsignedInt();
			_tprintf(_T("frameCount : %d\n"), frameCount);

			// generate update array
			CArray<int, int> updateArr;
			updateArr.SetSize(addressCount);

			//running time
			float Time;
			BOOL err;
			CHECK_TIME_START;

			queryStr = "select Address, Frame, Value from vtk.dumped_data where LABID = '" + labID + "' order by Address, Frame;";
			query->SetQuery(queryStr);
			//_tprintf(_T("%s\n"), CString(query->GetQuery()));
			query->Execute();

			bool ret;
			for(int addressNum = 0; addressNum < addressCount; addressNum++)
			{
				vtkVariant Address;
				vtkVariant Frame;
				vtkVariant Value;

				int oldValue = -1;
				int newValue = -1;
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
					Value = query->DataValue(2);

					if(frameNum != Frame.ToInt())
					{
						_tprintf(_T("frameNum error : %d, %d\n"), frameNum, Frame.ToInt());
						ret = false;
						break;
					}
					
					newValue = (int)strtol(Value.ToString().c_str(), NULL, 16);
					if(!(oldValue < 0) && oldValue != newValue)
					{
						updateCount += 1;
					}
					
					oldValue = newValue;
				}

				if(!ret)
				{
					break;
				}

				//_tprintf(_T("%s\n"), CString(Address.ToString().c_str()));
				if(addressNum != (int)strtol(Address.ToString().c_str(), NULL, 16))
				{
					_tprintf(_T("addressNum error : %d, %s\n"), addressNum, CString(Address.ToString().c_str()));
					break;
				}

				//_tprintf(_T("%d "), updateCount);
				updateArr.SetAt(addressNum, updateCount);
			}

			//running time
			CHECK_TIME_END(Time, err);
			if(err) _tprintf(_T("running time : %8.6f ms\n"), Time);

			for(int addressNum = 0; addressNum < addressCount; addressNum++)
			{
				_tprintf(_T("%d "), updateArr.GetAt(addressNum));
			}


			//for(int addressNum = 0; addressNum < addressCount; addressNum++)
			//{
			//	CString hexValue;
			//	hexValue.Format(_T("%04X"),addressNum);
			//	vtkStdString queryStr = "select * from vtk.dumped_data where LABID = '" + labID + "' and Address = '" + vtkStdString(CStringA(hexValue)) + "' order by Frame;";
			//	query->SetQuery(queryStr);
			//	//_tprintf(_T("%s\n"), CString(query->GetQuery()));
			//	query->Execute();

			//	//for( int col = 0; col < query->GetNumberOfFields(); col++)
			//	//{
			//	//	_tprintf(_T("%s\t"), CString(query->GetFieldName(col))); 
			//	//}
			//	//_tprintf(_T("\n"));

			//	int oldValue = -1;
			//	int newValue = -1;
			//	int updateCount = 0;
			//	while( query->NextRow() )
			//	{
			//		newValue = (int)strtol(query->DataValue(1).ToString().c_str(), NULL, 16);

			//		if(oldValue < 0)
			//		{
			//			//oldValue = newValue;
			//			//_tprintf(_T("oldValue is NULL\n"));
			//		}
			//		else
			//		{
			//			if (oldValue != newValue)
			//			{
			//				updateCount += 1;
			//			}
			//		}
			//		
			//		oldValue = newValue;

			//		//query->DataValue(0);
			//		//_tprintf(_T("value : %x, %d\n"), newValue, newValue);
			//	}

			//	//_tprintf(_T("updateCount is %d\n"), updateCount);

			//	vtkArr.SetAt(addressNum, updateCount);
			//}
		}
	}
	else
	{
		// TODO: 오류 코드를 필요에 따라 수정합니다.
		_tprintf(_T("심각한 오류: GetModuleHandle 실패\n"));
		nRetCode = 1;
	}

	system("PAUSE");

	return nRetCode;
}
