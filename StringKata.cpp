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
	string TestStr = "1,2";
	string NullStr = "";
	string Test0 = "123,321,111";

  cout << "NullStr ";
  cout << Add(NullStr) << endl;
  cout << "TestStr ";
  cout << Add(TestStr) << endl;
  cout << "Test0 ";
  cout << Add(Test0) << endl;
  return 0;
}
