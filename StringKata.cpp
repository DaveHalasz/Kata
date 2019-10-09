#include <iostream>
#include <sstream>
#include <string>
using namespace std ;


int Add(string numbers);

// Add the numbers
int Add(string numbers)
{
	int Total = 0;
	
	stringstream ss;
	ss << numbers;
	
	// Continue until done with the input string
	// Using a comma as the delimeter
	string temp;
	int found;
	while (getline(ss, temp, ','))
	{	
		// Check for an integer
		if (stringstream(temp) >> found )
			Total += found;
	}
	
	return Total;
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
	
	return 0;
}
