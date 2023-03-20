#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>
#include <utility>

class MathUtils
{
public:
	static std::vector<int> calcACF(const std::vector<int>& signal);

	static std::pair<int, int> countMPS(const std::vector<int>& acf);
};

#endif