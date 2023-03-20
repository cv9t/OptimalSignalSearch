#include "OptimalSignal.h"
#include "MathUtils.h"
#include <queue>
#include <algorithm>

int EMPTY = -1;

OptimalSignal::OptimalSignal(int length)
{
	// TODO:
	// Сделать проверку на длину последовательности, length >= 5

	_tree = new Tree(length / 2);
	_length = length;

	_mps = EMPTY;
	_mpsCount = EMPTY;

	_create();
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
	_create(_tree->getRoot(), {}, {});
}

void OptimalSignal::_create(Node* node, std::vector<int> lCode, std::vector<int> rCode)
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

		// if (node->isLeaf() || _mps != EMPTY) {
		if (node->isLeaf()) {
			std::vector<int> newSignal = lCode;
			newSignal.insert(newSignal.end(), rCode.begin(), rCode.end());

			std::vector<int> newAcf = MathUtils::calcACF(newSignal);
			std::pair<int, int> temp = MathUtils::countMPS(newAcf);

			int newMps = temp.first;
			int newMpsCount = temp.second;

			// TODO:
			// Доделать условия для выброса ненужных веток

			//if (!node->isLeaf() && (newMps > _mps || (newMps == _mps && newMpsCount > _mpsCount))) {
			//	return;
			//}

			if (_isOdd()) {
				int mid = _length / 2;
				newSignal.insert(newSignal.begin() + mid, -1);

				std::vector<int> acf_0 = MathUtils::calcACF(newSignal);
				temp = MathUtils::countMPS(acf_0);

				int mps_0 = temp.first;
				int mpsCount_0 = temp.second;

				newSignal[mid] = 1;

				std::vector<int> acf_1 = MathUtils::calcACF(newSignal);
				temp = MathUtils::countMPS(acf_1);

				int mps_1 = temp.first;
				int mpsCount_1 = temp.second;

				if (mps_0 < mps_1 || (mps_0 == mps_1 && mpsCount_0 > mpsCount_1)) {
					newMps = mps_0;
					newAcf = acf_0;
					newMpsCount = mpsCount_0;
				}
				else {
					newMps = mps_1;
					newAcf = acf_1;
					newMpsCount = mpsCount_1;
				}
			}

			if (_mps == EMPTY || newMps < _mps || (newMps == _mps && newMpsCount > _mpsCount)) {
				_mps = newMps;
				_mpsCount = newMpsCount;
				_signal = newSignal;
				_acf = newAcf;
			}
		}
	}

	for (Node* child : node->getChildren()) {
		_create(child, lCode, rCode);
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

	os << "mpsCount: " << signal._mpsCount << std::endl;

	return os;
}