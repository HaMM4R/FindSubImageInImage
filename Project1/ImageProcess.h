#pragma once
#include<string>

using namespace std; 

class Base_Image
{
public:
	double *data;
	string file;
	int columns;
	int rows; 
	Base_Image();
	Base_Image(string fileName);
	int getGrayscaleVal(int rows, int columns, int columnLength);
};

class Ref_Image : public Base_Image
{
public:
	Ref_Image(string fileName);
};

class Large_Image : public Base_Image
{
public:
	Large_Image(string fileName);
	void changeImage(double x, double y, int columns, int rows, int large);
	void DrawPGM();
};