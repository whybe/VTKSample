#pragma once

#include "resource.h"

#include <vtkSmartPointer.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkIOMySQL)

#define LABID "asds"

#define CHECK_TIME_START  __int64 freq, start, end; if (QueryPerformanceFrequency((_LARGE_INTEGER*)&freq))  {QueryPerformanceCounter((_LARGE_INTEGER*)&start);

#define CHECK_TIME_END(a,b) QueryPerformanceCounter((_LARGE_INTEGER*)&end);  a=(float)((double)(end - start)/freq*1000); b=TRUE;} else b=FALSE;