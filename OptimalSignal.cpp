#include "OptimalSignal.h"
#include "MathUtils.h"
#include <queue>
#include <algorithm>

#include <iostream>

OptimalSignal::OptimalSignal(int length)
{
	// TODO:
	// Сделать проверку на длину последовательности, length >= 5

	_tree = new Tree(length / 2);
	_length = length;

	// std::cout << *_tree;

	// _create();
}

OptimalSignal::~OptimalSignal()
{
	delete _tree;
	_signal.clear();
	_acf.clear();
}

bool OptimalSignal::_isOdd()
{
	return _length % 2 == 1;
}

void OptimalSignal::_create()
{
	std::vector<int> lCode, rCode;
	_create(_tree->getRoot(), lCode, rCode);
}

void OptimalSignal::_create(Node* node, std::vector<int>& lCode, std::vector<int>& rCode, bool mpsFound)
{
	if (node == nullptr) return;

	if (!node->isRoot()) {
		int levelDiff = lCode.size() - node->getParent()->getLevel();
		if (levelDiff > 0) {
			lCode.erase(lCode.end() - levelDiff, lCode.end());
			rCode.erase(rCode.begin(), rCode.begin() + levelDiff);
		}

		int val1 = node->getValue().first;
		int val2 = node->getValue().second;

		lCode.push_back(val1);
		rCode.insert(rCode.begin(), val2);

		if (node->isLeaf()) {
			std::vector<int> newSignal = lCode;
			newSignal.insert(newSignal.end(), rCode.begin(), rCode.end());

			std::vector<int> newAcf = MathUtils::calcACF(newSignal);
			/* std::pair<int, int> mpsData = MathUtils::calcMPS(newAcf);

			int newMps = mpsData.first;
			int newMpsOffset = mpsData.second;

			if (_isOdd()) {
				int mid = _length / 2;
				newSignal.insert(newSignal.begin() + mid, -1);

				std::vector<int> acf_0 = MathUtils::calcACF(newSignal);
				mpsData = MathUtils::calcMPS(acf_0);

				int mps_0 = mpsData.first;
				int mpsOffset_0 = mpsData.second;

				newSignal[mid] = 1;

				std::vector<int> acf_1 = MathUtils::calcACF(newSignal);
				mpsData = MathUtils::calcMPS(acf_1);

				int mps_1 = mpsData.first;
				int mpsOffset_1 = mpsData.second;

				if (mps_0 < mps_1 || (mps_0 == mps_1 && mpsOffset_0 > mpsOffset_1)) {
					newMps = mps_0;
					newAcf = acf_0;
					newMpsOffset = mpsOffset_0;
				}
				else {
					newMps = mps_1;
					newAcf = acf_1;
					newMpsOffset = mpsOffset_1;
				}
			}*/

			//for (int i = 0; i < newSignal.size(); i += 1) {
			//	std::cout << newSignal[i] << " ";
			//}
			//std::cout << "  ";

			for (int i = 0; i < newAcf.size(); i += 1) {
				std::cout << newAcf[i];
			}
			std::cout << std::endl;

			/*if (newMps != 0 && (!mpsFound || newMps < _mps || (newMps == _mps && newMpsOffset > _mpsOffset))) {
				mpsFound = true;
				_mps = newMps;
				_mpsOffset = newMpsOffset;
				_signal = newSignal;
				_acf = newAcf;
			}*/
		}
	}

	for (Node* child : node->getChildren()) {
		_create(child, lCode, rCode, mpsFound);
	}
}

std::ostream& operator<<(std::ostream& os, OptimalSignal& signal)
{
	os << "signal: [ ";
	for (int i = 0; i < signal._signal.size(); i += 1) {
		os << signal._signal[i] << " ";
	}
	os << "]" << std::endl;

	os << "acf: [ ";
	for (int i = 0; i < signal._acf.size(); i += 1) {
		os << signal._acf[i] << " ";
	}
	os << "]" << std::endl;

	os << "mps: " << signal._mps << std::endl;

	os << "mpsOffset: " << signal._mpsOffset << std::endl;

	return os;
}