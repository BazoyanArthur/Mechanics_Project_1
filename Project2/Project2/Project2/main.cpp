#include <iostream>
#include "System.h"

int main()
{
	Mass M1(10, 10, 5);
	Mass M2(8, 10, 4);
	Mass M3(10, 8, 2);

	System Sys(M1, M2, M3, 0.3, 0.3, 0.3, 100 );

	Sys.PUSH();

	return 0;
}