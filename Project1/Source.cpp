#include <iostream>
#include <vector>
#include <algorithm>
#include "ImageProcess.h"
#include "Matrix.h"

using namespace std;

//Struct to hold the X and Y coordianates of a section taken from the cluttered image
//Also stores how similar it is to the reference image.
struct matches
{
	int xCo;
	int yCo;
	double similarity; 

	bool operator() (matches a, matches b)
	{
		return (a.similarity < b.similarity);
	};
} match; 


int main()
{
	char error = 'e';
	int numberOfMatches = 0; 

	double* testSet;
	double similarity;
	vector<matches> results;		//Vector to hold the results of the comparision between a section of the large image and the reference image

	string ref = "Wally_grey";
	string large = "Cluttered_scene";
	Ref_Image *refImage = new Ref_Image((char*)ref.c_str());				//When object creates it passes the reference filename to the constructor
	Large_Image *largeImage = new Large_Image((char*)large.c_str());		//When object creates it passes the large image filename to the constructor

	//If a user accidently enters a character rather than a number this will loop through until the user enters a valid number 
	while (numberOfMatches == 0)
	{
		//Exception handling to prevent a crash if a user were to enter anything other than a number 
		try
		{
			cout << "Enter the number of matches you would like to find" << endl;
			cin >> numberOfMatches;
			if (!cin)
				throw error;
		}
		catch (...)
		{
			cin.clear(); 
			cin.ignore(); 
			cout << "Please enter a number" << endl;
		}
	}

	cout << "Searching..." << endl;

	//A loop to iterate through the whole of the large image two pixels at a time across the X and the Y axis
	//It will stop at a distance equal to the size of the reference image on both the X and the Y axis. 
	for (int i = 0; i < largeImage->rows - refImage->rows; i+=2)
	{
		for (int j = 0; j < largeImage->columns - refImage->columns; j+=2)
		{
			testSet = returnTestSet(i, j, refImage->rows, refImage->columns, largeImage->columns, largeImage->data);	//Sections off a piece of the large image to be tested against the reference image
			similarity = calculateSimilarity(refImage->data, testSet, (refImage->rows * refImage->columns));		//Calculates the similarity between the reference and the piece sectioned off above
			results.push_back({ i, j,similarity });		//pushes the results into a vector for later sorting 

			delete testSet;
		}
	}
	
	sort(results.begin(), results.end(), match);		//Sorts the results of the of the previous loop by similarity values 

	//Loop to change the main image and output the results to the user based on how many results the user wanted to find 
	for (int i = 0; i < numberOfMatches; i++)
	{
		largeImage->changeImage(results[i].yCo, results[i].xCo, refImage->columns, refImage->rows, largeImage->columns);	//Changes the greyscale values held in data in order to draw a rectange around wally and the other matches
		if(i == 0)
			cout << "Closest Match at position: " << results[i].yCo << "," << results[i].xCo << " Similarity value: " << results[i].similarity << endl;
		else 
			cout << "Match " << i + 1 << " at position: " << results[i].yCo << "," << results[i].xCo << " Similarity value: " << results[i].similarity << endl;
	}

	largeImage->DrawPGM();		//Outputs the data to a PGM 

	delete refImage; 
	delete largeImage; 

	cin.get();
	return 0;
}