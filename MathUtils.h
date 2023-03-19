#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>

class MathUtils
{
public:
	static std::vector<int> calcACF(const std::vector<int>& signal);

	static int calcMPS(const std::vector<int>& acf);
};

#endif