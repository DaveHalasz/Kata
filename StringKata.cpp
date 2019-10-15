#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include <vector>
using namespace std ;

char invalidTmp[31];
struct AddException : public exception {
	const char * what() const throw() {
		return "Add Exception";
	}
};

int Add(string numbers);

// Supporting function
// Parse the delimeters into delim
// Return the location past the delimeters
int GetDelimeter(string numbers, vector<string> &delim);
// When processing the numbers, provide the index to the next delimeter being used
int  GetDelimIndex(string numbers, vector<string> &delim, int offset);

// Add the numbers which are contained in the string
int Add(string numbers)
{	
	int Total = 0;
	int inputMax = 1000;
	
	stringstream invalid;
	int errorFound = 0;
	
	stringstream ss;
	//ss << numbers;
	
	// Get the delimeter from the beginning of the string
	vector<string> delim;
	int endDelimPos = GetDelimeter(numbers, delim);
		
	// remove the delimeters
	numbers.erase(0, endDelimPos);
	ss << numbers;
	
	// Continue until done with the input string
	// First get a line, second pars the line with the delimeter
	// Getting a line first fixes an issue with Test3A
	string temp, templine;
	int found;
	while (getline(ss, templine))
	{
		// Parse the line with the delimeter
		temp = "";
		int position = 0;
		int endIsFound = 0;
		int delimIndex = GetDelimIndex(templine,delim,0);
		int delimPos = templine.find(delim[delimIndex]);
		if ( delimPos >=0 )
			temp = templine.substr(position, delimPos);
		else
		{
			temp = templine.substr(position);
			endIsFound = 1;			
		}


		// endIsFound becomes true when found the end of the string
		// Done becomes true when finished processing up to the end of the string
		int Done = 0;
		while ( !Done )
		{
			// Check for an integer
			if (stringstream(temp) >> found )
			{
				// Check for an invalid negative number
				if ( found < 0 )
				{
					errorFound = 1;
					invalid << found;
					invalid << " ";
				}
				else
				{
					// Check for input being too large
					// Step 6 indicates to skip the value, if too large
					if ( found <= inputMax )
						Total += found;
				}
			}
			
			// Check if finished processing
			if ( endIsFound )
				Done = 1;
			else
			{
				// Looking for the next delimeter
				temp = "";
				position = delimPos+delim[delimIndex].size();
				delimIndex = GetDelimIndex(templine,delim,delimPos+1);
				if ( delimIndex < 0 ) 
					delimPos = delimIndex;		// Not found
				else
					delimPos = templine.find(delim[delimIndex],delimPos+1);

				// Check if didn't find the delimeter
				if ( delimPos >= 0 )
					temp = templine.substr(position, delimPos);
				else
				{
					temp = templine.substr(position);
					endIsFound = 1;				
				}
			}
		}
	}
	
	// Check if we had an error. If yes, throw an exception
	if ( errorFound )
	{
		// Copy the invalid values into const char memory
		strncpy( invalidTmp, invalid.str().c_str(), 30);
		throw invalidTmp;
	}
	return Total;
}

// Get the delimeter
// If there is no delimeter defined then default is comma
// Delimeter starts with // and end with new line
// Return the location past the delimeters
int GetDelimeter(string numbers, vector<string> &delim)
{
	string delimStart = "//";
	char beginDelimStr = '[';
	string endDelimStr = "]";
	int endDelimPos;
	int beginDelimPos = 3;	// If multiple delimeters then after "//[" is the beginning
	string tempdelim = ",";
	char tempChar;
	int delimHasBeenSet = 0;
	int FinishedWithDelimPos = 0;

	// Check for the delimeter markings at the begining of the string. The "//".
	if ( !strncmp(numbers.c_str(), delimStart.c_str(), delimStart.size()) )
	{
		FinishedWithDelimPos = 4;	// Single delimeter, without []
		// Check that the string isn't limited to the delimStart
		// If there is another character then it is the delimeter
		if ( numbers.size() > delimStart.size() )
		{
			tempChar = numbers.at(delimStart.size());
			// Check if the delimeter will be a string. If yes, begins with a [
			if (tempChar == beginDelimStr)
			{
				// Done gets set when all of the multiple delimeters have been handled
				int Done = 0;
				while (!Done)
				{
					// Handle string delimeter input
					endDelimPos = numbers.find(endDelimStr,beginDelimPos);
					// Check if found the end of the line instead of the end delimeter
					if ( endDelimPos <= 0)
					{
						tempdelim = numbers.substr(beginDelimPos);
						Done = 1;
					}
					else
					{
						tempdelim = numbers.substr(beginDelimPos, (endDelimPos-beginDelimPos));
						FinishedWithDelimPos = endDelimPos+2;
					}
						
						
						
					// Set the delimeter that was found
					delim.push_back(tempdelim);
					delimHasBeenSet = 1;
						
					// Check if there is another delimeter string
					// If not then we are done finding the delimeters
					// Check if there is room for another delimeter
					// The endDelimPos+2 is position of x in "//[d][x"
					if (numbers.size() > endDelimPos+2)
					{
						// Check if found the begining of delimeter again
						tempChar = numbers.at(endDelimPos+1);
						if (tempChar == beginDelimStr)
						{
							// Yes, there is another delimeter
							// Setup for next time through the while loop
							beginDelimPos = endDelimPos+2;
						}
						else
							Done = 1;
					}
					else
					{
						Done = 1;
					}
				}
			}
			else
			{
				// There is only one delimeter and it is not enclosed in []
				tempdelim = tempChar;
			}
		
		}

	}
	
	// Handle saving the delimeter in the cases of a single delimeter
	if (!delimHasBeenSet)
		delim.push_back(tempdelim);

	return FinishedWithDelimPos;
}

// When processing the numbers, provide the index to the next delimeter being used
int  GetDelimIndex(string numbers, vector<string> &delim, int offset)
{
	int templowest = -1;
	int templowestIndex = -1;
	int i = 0;
	int foundOne = 0;
	
	// Find the 
	while ( i < delim.size() )
	{
		int pos = numbers.find(delim[i], offset);
		if ( pos >= 0 )
		{
			foundOne = 1;
			if ( templowest < 0 )
			{
				templowest = pos;
				templowestIndex = i;
			}
			else
			{
				if ( pos < templowest )
				{
					templowest = pos;
					templowestIndex = i;
				}
			}
		}
		i++;
	}
	
	if ( !foundOne ) return -1;
	else return templowestIndex;
}

int main( int argc, char *argv[] )
{
	// Test cases for the first two steps
	string TestStr = "1,2";
	string NullStr = "";
	string Test0 = "123,321,111";

	// Test cases for step 3
	string Test3A = "1\n2,3";
	// Note : Step 3 indicates the following is invalid input
	// Assuming ok to handle, even though not valid input
	string Test3B = "1,\n2";
	
	// Test cases for step 4
	string Test4A = "//;\n1;7";
	
	// Test cases for step 5
	string Test5A = "1,-7,3,-8";
	
	// Test case for step 6
	string Test6A = "1001, 2";
	string Test6B = "2, 1000";
	
	// Test case for step 7
	string Test7A = "//[***]\n1***2***3";
	
	// Test case for step 8
	string Test8A = "//[*][%]\n1*2%3";
	string Test8B = "//[**][%%]\n4**5%%6";
	
	struct TestStrStruct {
		string TestDescription;
		string TestStr;
	};
	TestStrStruct TestList[] = { {"NullStr ", NullStr}, 
								{"TestStr ", TestStr}, 
								{"Test0 ", Test0}, 
								{"Test3A ", Test3A}, 
								{"Test3B ", Test3B}, 
								{"Test4A ", Test4A}, 
								{"Test5A ", Test5A}, 
								{"Test6A ", Test6A}, 
								{"Test6B ", Test6B},
								{"Test7A ", Test7A},
								{"Test8A ", Test8A},
								{"Test8B ", Test8B} };

	TestStrStruct TestListA[] = { {"TestStr ", TestStr } };

	// Run the unit tests
	int i;
	for ( i=0; i < (sizeof(TestList)/sizeof(TestStrStruct)); i++)
	{
		try {
			cout << TestList[i].TestDescription;
			cout << Add(TestList[i].TestStr) << endl << endl;
		} catch (const char* msg) {
			cout << "Add() error\n  Invalid input is ";
			cout << msg << endl << endl;
		}
	};
	
	return 0;
}
