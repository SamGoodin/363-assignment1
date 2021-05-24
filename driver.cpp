#include <iostream>
#include <exception>
#include <stdexcept>
#include "Array.h"
using namespace std;

int main (int argc, char * argv [])
{
	Array a1;


	a1.resize(20);
	Array a2;
	a2.resize(15);
	a1 = a2;
	bool idk = (a1 == a2);
	cout << idk;

	return 0;
}
