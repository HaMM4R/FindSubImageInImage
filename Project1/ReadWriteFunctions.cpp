#include <iostream>
#include <fstream>
#include <string>
#include "ReadWriteFunctions.h"

using namespace std; 

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
// Read .txt file with image of size (R rows x C columns), and convert to an array of doubles

//Counts number of rows in a file
int countRows(char *fileName)
{
	int numOfLines = 0;
	string text; 
	ifstream myfile(fileName);

	cout << "Counting rows for " << fileName << endl; 

	while (getline(myfile, text))		//Increments the number of lines by 1 for every line in the file
		numOfLines++; 
		
	myfile.close();
	return numOfLines; 
}

//Counts the number of columns in a file
int countColumns(char *fileName)
{
	int numOfRows = 0;
	char nextChar;
	string text;
	ifstream myfile(fileName);
	getline(myfile, text);

	cout << "Counting columns for " << fileName << endl;

	for (int i = 0; i<int(text.length()); i++)
	{
		nextChar = text.at(i);		//Get character
		if (isspace(text[i]))		//Increments the number of rows by 1 for every space in the file
			numOfRows++;
	}

	myfile.close();
	return numOfRows / 2;		//Divides the number of rows by two as there are two spaces inbetween each entry. 
}


double* read_text(char *fileName, int sizeR, int sizeC)
{
	cout << "Reading data from " << fileName << endl; 
	double* data = new double[sizeR*sizeC];
	int i=0;
	ifstream myfile (fileName);
	if (myfile.is_open())
	{
	 
		while ( myfile.good())
		{
			if (i>sizeR*sizeC-1) break;
				myfile >> *(data+i);
			 //cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
				i++;                                                             
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 
	//cout << i;

	return data;
}



// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and 1 for binary images.
void write_pgm(char *filename, double *data, int sizeR, int sizeC, int Q)
{
	cout << "Writing data to .pgm, image can be found in the Project1 sub folder and is called " << filename << endl;
	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char [sizeR*sizeC];

	// convert the integer values to unsigned char
 
	for(i=0; i<sizeR*sizeC; i++)
		image[i]=(unsigned char)data[i];

	myfile.open(filename, ios::out|ios::binary|ios::trunc);

	if (!myfile) 
	{
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) 
	{
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete [] image;
}
