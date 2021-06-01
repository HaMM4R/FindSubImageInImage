#include <iostream>
#include "Matrix.h"

using namespace std; 

//Takes a chunk of the large image ready to be compared to the small image 
double* returnTestSet(double x, double y, int rowLength, int columnLength, int LargeLength, double* data)
{
	int size = rowLength * columnLength;
	double* test = new double[size];
	int rowCounter = 0;
	int offset = (x * LargeLength) + y;		//Ensures the loop starts in the correct position 
	
	//Loops through the data in the large image to get an image the same size as the reference 
	//Uses pointer aritmetic to ensure the correct values are taken and the corrent points for rows are skipped to 
	for (int i = 0; i < size; i++)
	{
		if ((i % columnLength == 0 && i != 0))
		{
			rowCounter++;
		}

		test[i] = data[(i + offset + (rowCounter * LargeLength)) - (rowCounter * columnLength)];
	}


	return test;
}

//Sorensen distance is used to calculate the similarity between the reference image and a section taken from the large image
double calculateSimilarity(double* ref, double* large, int size)
{
	double similar = 0;
	double valueOne = 0;
	double valueTwo = 0;

	for (int i = 0; i < size; i++)
	{
		valueOne += abs(ref[i] - large[i]);
		valueTwo += ref[i] + large[i];
	}

	similar = valueOne / valueTwo;

	return similar;
}
