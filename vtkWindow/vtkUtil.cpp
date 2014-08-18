#include "stdafx.h"
#include "vtkUtil.h"

//template <typename T> void vtkUtil::PrintColour(T &rgb)
//{
//	// Don't do this in real code! Range checking etc. is needed.
//	for (size_t i = 0; i < 3; ++i)
//	{
//		if (i < 2)
//		{
//			std::cout << static_cast<double>(rgb[i]) << " ";
//		}
//		else
//		{
//			std::cout << static_cast<double>(rgb[i]);
//		}
//	}
//}

//! Use a color transfer Function to generate the colors in the lookup table.
void vtkUtil::MakeLUTFromCTF(size_t const & tableSize, vtkLookupTable *lut, size_t const &arrSize, vtkIntArray *arr, int minValue, int maxValue)
{
	vtkSmartPointer<vtkColorTransferFunction> ctf = vtkSmartPointer<vtkColorTransferFunction>::New();
	ctf->SetColorSpaceToDiverging();
	// White to Blue.
	ctf->AddRGBPoint(0.0, 1.000, 1.000, 1.000);
	ctf->AddRGBPoint(0.5, 1.000, 0.750, 0.000);
	ctf->AddRGBPoint(1.0, 1.000, 0.000, 0.000);

	lut->SetNumberOfTableValues(tableSize);
	lut->Build();

	// Get min and max
	//int renge[2];
	//arr->GetValueRange(renge); // Note this is not GetRange()!
	//std::cout << "min : " << renge[0] << ", max : " << renge[1] << std::endl;
	std::cout << "min : " << minValue << ", max : " << maxValue << std::endl;

	for(size_t i = 0; i < arrSize; ++i)
	{
		//std::cout << "arr[" << i << "] : " << arr->GetValue(i) << std::endl;
		//double *rgb = ctf->GetColor(static_cast<double>(arr->GetValue(i)-renge[0])/(renge[1]-renge[0]));
		double *rgb = ctf->GetColor(static_cast<double>(arr->GetValue(i)-minValue)/(maxValue-minValue));
		lut->SetTableValue(i,rgb);
	}

	vtkSmartPointer<vtkNamedColors> nc = vtkSmartPointer<vtkNamedColors>::New();

	for(size_t i = arrSize; i < tableSize; ++i)
	{
		lut->SetTableValue(i, nc->GetColor4d("Black").GetData());
	}
}

//! Create the cell data using the colors from the lookup table.
void vtkUtil::MakeCellData(size_t const & tableSize, vtkLookupTable *lut,
	vtkUnsignedCharArray *colors)
{
	for (size_t i = 0; i < tableSize; i++)
	{
		double rgb[3];
		unsigned char ucrgb[3];
		// Get the interpolated color.
		// Of course you can use any function whose range is [0...1]
		// to get the required color and assign it to a cell Id.
		// In this case we are just using the cell (Id + 1)/(tableSize - 1)
		// to get the interpolated color.
		lut->GetColor(static_cast<double>(i) / (tableSize), rgb);
		for (size_t j = 0; j < 3; ++j)
		{
			ucrgb[j] = static_cast<unsigned char>(rgb[j] * 255);
		}
		colors->InsertNextTuple3(ucrgb[0], ucrgb[1], ucrgb[2]);
		// Print out what we have.
		//std::cout << "(";
		//PrintColour<double[3]>(rgb);
		//std::cout << ") (";
		//PrintColour<unsigned char[3]>(ucrgb);
		//std::cout << ")" << std::endl;
	}
}

void vtkUtil::MakeXYFromLength(int &x, int &y, int &length)
{

}

//template <typename T> std::string vtkUtil::int_to_hex(T i)
//{
//	std::stringstream stream;
//	stream 
//		<< "0x"
//		<< std::setfill ('0') << std::setw(sizeof(T)*2) 
//		<< std::hex << i;
//	return stream.str();
//}