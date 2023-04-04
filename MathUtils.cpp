#include "MathUtils.h"
#include <cmath>

std::vector<int> MathUtils::calcACF(const std::vector<int>& signal)
{
	// TODO:
	// Сделать проверку на размер входного вектора

	int n = signal.size();
	std::vector<int> acf(n, 0);

	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n - i; j += 1) {
			acf[i] += signal[j] * signal[j + i];
		}
		acf[i] = std::abs(acf[i]);
	}

	return acf;
}

std::pair<int, int> MathUtils::calcMPS(const std::vector<int>& acf)
{
	// TODO:
	// Сделать проверку на размер входного вектора

	//int n = acf.size();
	//int mps = 0;
	//int offset = 0;

	//for (int i = 1; i < n - 1; i += 1) {
	//	int curr = std::abs(acf[i]);
	//	int prev = std::abs(acf[i - 1]);
	//	int next = std::abs(acf[i + 1]);
	//	
	//	if (curr > prev && curr > next && curr > mps) {
	//		mps = curr;
	//		offset = i;
	//	}
	//}

	////int prevL = std::abs(acf[n - 2]);
	////int last = std::abs(acf[n - 1]);

	//////if (last > prevL && last > mps) {
	//////	mps = last;
	//////	offset = n - 1;
	//////}

	//return std::make_pair(mps, offset);
	return std::make_pair(0, 0);
}