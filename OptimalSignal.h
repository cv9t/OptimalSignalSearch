#ifndef OPTIMAL_SIGNAL_H
#define OPTIMAL_SIGNAL_H

#include "Tree.h"
#include <vector>
#include <fstream>

class OptimalSignal
{
private:
	Tree* _tree;
	std::vector<int> _signal, _acf;
	int _length, _mps, _mpsCount;

	bool _isOdd();

	void _create();

	void _create(Node* root, std::vector<int> lCode, std::vector<int> rCode);

public:
	OptimalSignal(int length);
	~OptimalSignal();

	friend std::ostream& operator<<(std::ostream& os, OptimalSignal& signal);
};

#endif