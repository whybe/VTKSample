#ifndef VTKUTIL_H
#define VTKUTIL_H

#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkIntArray.h>
#include <vtkNamedColors.h>
#include <iostream>

template <typename T> void PrintColour(T &rgb);
//void MakeLUTFromCTF(size_t const & tableSize, vtkLookupTable *lut);
void MakeLUTFromCTF(size_t const & tableSize, vtkLookupTable *lut, size_t const &arrSize, vtkIntArray *arr);
void MakeCellData(size_t const & tableSize, vtkLookupTable *lut, vtkUnsignedCharArray *colors);
void MakeXYFromLength(int &x, int &y, int &length);

#endif //VTKUTIL_H