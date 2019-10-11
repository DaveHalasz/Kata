#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <exception>
using namespace std ;

char invalidTmp[31];
struct AddException : public exception {
	const char * what() const throw() {
		return "Add Exception";
	}
};

int Add(string numbers);

char GetDelimeter(string numbers);

// Add the numbers which are contained in the string
int Add(string numbers)
{	
	int Total = 0;
	
	stringstream invalid;
	int errorFound = 0;
	
	stringstream ss;
	stringstream ss2;
	ss << numbers;
	
	// Get the delimeter from the beginning of the string
	char delim = GetDelimeter(numbers);
	
	// Continue until done with the input string
	// First get a line, second pars the line with the delimeter
	// Getting a line first fixes an issue with Test3A
	string temp, templine;
	int found;
	while (getline(ss, templine))
	{
		// Now parse through the line
		ss2 << templine;
	
		// Parse the line with the delimeter
		while (getline(ss2, temp, delim))
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
					Total += found;
			}
		}
		ss2.clear();
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
char GetDelimeter(string numbers)
{
	string delimStart = "//";
	char delim = ',';

	// Check for the delimeter markings at the begiining of the string
	if ( !strncmp(numbers.c_str(), delimStart.c_str(), delimStart.size()) )
	{
		// Check that the string isn't limited to the delimStart
		// If there is another character then it is the delimeter
		if ( numbers.size() > delimStart.size() )
			delim = numbers.at(delimStart.size());
		
	}
	return delim;
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
	
	struct TestStrStruct {
		string TestDescription;
		string TestStr;
	};
	TestStrStruct TestList[] = { {"NullStr ", NullStr}, {"TestStr ", TestStr}, {"Test0 ", Test0}, {"Test3A ", Test3A}, {"Test3B ", Test3B}, {"Test4A ", Test4A}, {"Test5A ", Test5A} };


	// Run the unit tests
	int i;
	for ( i=0; i < (sizeof(TestList)/sizeof(TestStrStruct)); i++)
	{
		try {
			cout << TestList[i].TestDescription;
			cout << Add(TestList[i].TestStr) << endl;
		} catch (const char* msg) {
			cout << "Add() error\n  Invalid input is ";
			cout << msg << endl;
		}
	};
	
	return 0;
}
