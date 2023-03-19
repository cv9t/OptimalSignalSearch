#include <iostream>
#include "OptimalSignal.h"

int main()
{
	OptimalSignal* signal = new OptimalSignal(6);

	std::cout << *signal << std::endl;

	return 0;
}