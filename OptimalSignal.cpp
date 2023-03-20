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
	if (node == nullptr) {
		return;
	}

	if (!node->isRoot()) {
		int levelDiff = lCode.size() - node->getParent()->getLevel();
		if (levelDiff > 0) {
			lCode.erase(lCode.end() - levelDiff, lCode.end());
			rCode.erase(rCode.begin(), rCode.begin() + levelDiff);
		}

		int val1 = std::get<0>(node->getValue());
		int val2 = std::get<1>(node->getValue());

		lCode.push_back(val1);
		rCode.insert(rCode.begin(), val2);

		if (node->isLeaf() || _mps != EMPTY) {
			std::vector<int> newSignal = lCode;
			newSignal.insert(newSignal.end(), rCode.begin(), rCode.end());

			std::vector<int> newAcf = MathUtils::calcACF(newSignal);
			int newMps = MathUtils::calcMPS(newAcf);

			if (!node->isLeaf() && newMps > _mps) {
				return;
			}

			if (node->isLeaf()) {
				if (_isOdd()) {
					int mid = _length / 2;
					newSignal.insert(newSignal.begin() + mid, -1);

					std::vector<int> acf_0 = MathUtils::calcACF(newSignal);
					int mps_0 = MathUtils::calcMPS(acf_0);

					newSignal[mid] = 1;

					std::vector<int> acf_1 = MathUtils::calcACF(newSignal);
					int mps_1 = MathUtils::calcMPS(acf_1);

					if (mps_0 < mps_1) {
						newMps = mps_0;
						newAcf = acf_0;
					}
					else {
						newMps = mps_1;
						newAcf = acf_1;
					}
				}

				if (newMps < _mps || _mps == -1) {
					_mps = newMps;
					_signal = newSignal;
					_acf = newAcf;
				}
			}
		}
	}

	for (Node* child : node->getChildren()) {
		_create(child, lCode, rCode);
	}
}

std::ostream& operator<<(std::ostream& os, OptimalSignal& signal)
{
	os << "[ ";
	for (int i = 0; i < signal._signal.size(); i += 1) {
		os << signal._signal[i] << " ";
	}
	os << "]";

	os << "  " << "[ ";
	for (int i = 0; i < signal._acf.size(); i += 1) {
		os << signal._acf[i] << " ";
	}
	os << "]";

	os << "  " << signal._mps;

	return os;
}