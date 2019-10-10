#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
using namespace std ;


int Add(string numbers);

char GetDelimeter(string numbers);

// Add the numbers which are contained in the string
int Add(string numbers)
{
	int Total = 0;
	
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
				Total += found;
		}
		ss2.clear();
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

	// Run the first two steps unit tests
	cout << "NullStr ";
	cout << Add(NullStr) << endl;
	cout << "TestStr ";
	cout << Add(TestStr) << endl;
	cout << "Test0 ";
	cout << Add(Test0) << endl;
	
	// Run the step 3 unit tests
	cout << "Test3A ";
	cout << Add(Test3A) << endl;
	cout << "Test3B ";
	cout << Add(Test3B) << endl;
	
	// Run the step 4 unit tests
	cout << "Test4A ";
	cout << Add(Test4A) << endl;
	
	return 0;
}
