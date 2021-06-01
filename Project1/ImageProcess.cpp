#include <iostream>
#include "ReadWriteFunctions.h"
#include "ImageProcess.h"

using namespace std; 

double* data; 
int columns;
int rows; 
string file;

Base_Image::Base_Image()
{

}

//Base constructer that handles appropriate file extensions and reading in of data  
Base_Image::Base_Image(string fileName)
{
	file = fileName;

	file = file + ".txt";
	int i = 0; 
	columns = countColumns((char*)file.c_str());			
	rows = countRows((char*)file.c_str());					
	data = read_text((char*)file.c_str(), rows, columns);		//Reads in file with the number of rows and columns calculated above
}

//Changes values in the data array to 0 in order to draw a rectange around matches 
void Large_Image::changeImage(double x, double y, int columns, int rows, int large)
{
	//Pointer aritmetic is used in order to change the correct values
	//As it is a 1D array it must skip through the array by the width of the large image as so it changes the values in the correct place
	for (int i = x; i < x + columns; i++)
	{
		for (int j = y; j < y + rows; j++)
		{
			if((j < y + 3 || j >= (y + rows) - 3) || (i < x + 3 || i > ( x + columns) - 4))		//Prevents for loop from setting values inside the outline of the rectange to 0 to stop it from being filled in black
				*((data + i) + (large * j)) = 0;
		}
	}
}

//Writes out to PGM 
void Large_Image::DrawPGM()
{
	file.resize(file.size() - 4);		//Removes .txt from the end of the filename and replaces with .pgm 
	file = file + ".pgm";

	write_pgm((char*)file.c_str(), data, rows, columns, 255);
}

int Base_Image::getGrayscaleVal(int rows, int columns, int columnLength)
{
	return *(data + ((columns * columnLength) + rows));
}

//Calls the base constructor and passes through correct file name
Ref_Image::Ref_Image(string fileName) : Base_Image(fileName)
{
	cout << "";
}

//Calls the base constructor and passes through correct file name
Large_Image::Large_Image(string fileName) : Base_Image(fileName)
{
	cout << "";
}
