#include <iostream>
#include "OptimalSignal.h"
#include "MathUtils.h"

int main()
{
	OptimalSignal* signal = new OptimalSignal(13);

	std::cout << *signal;

	return 0;
}