#ifndef VTKUTIL_H
#define VTKUTIL_H

#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkIntArray.h>
#include <vtkNamedColors.h>
#include <iostream>
#include <sstream>
#include <string>

class vtkUtil
{
public:
	template <typename T> static void PrintColour(T &rgb)
	{
		// Don't do this in real code! Range checking etc. is needed.
		for (size_t i = 0; i < 3; ++i)
		{
			if (i < 2)
			{
				std::cout << static_cast<double>(rgb[i]) << " ";
			}
			else
			{
				std::cout << static_cast<double>(rgb[i]);
			}
		}
	};
	//void MakeLUTFromCTF(size_t const & tableSize, vtkLookupTable *lut);
	static void MakeLUTFromCTF(size_t const & tableSize, vtkLookupTable *lut, size_t const &arrSize, vtkIntArray *arr);
	static void MakeCellData(size_t const & tableSize, vtkLookupTable *lut, vtkUnsignedCharArray *colors);
	static void MakeXYFromLength(int &x, int &y, int &length);

	template <typename T> static std::string int_to_hex(T i)
	{
		std::stringstream stream;
		stream 
			<< "0x"
			<< std::setfill ('0') << std::setw(sizeof(T)) 
			<< std::hex << i;
		return stream.str();
	};
};
#endif //VTKUTIL_H