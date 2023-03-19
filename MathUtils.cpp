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
	}

	return acf;
}

int MathUtils::calcMPS(const std::vector<int>& acf)
{
	// TODO:
	// Сделать проверку на размер входного вектора

	int n = acf.size();
	int mps = acf[0];

	for (int i = 1; i < n; i += 1) {
		int curr = std::abs(acf[i]);
		int prev = std::abs(acf[i - 1]);

		if (i < n - 1) {
			int next = std::abs(acf[i + 1]);
			if (curr > prev && curr > next && curr < mps) {
				mps = curr;
			}
		}
		else if (curr > prev && curr < mps) {
			mps = curr;
		}
	}

	return mps;
}