#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include "Node.h"
#include <fstream>

class TreeUtils
{
private:
	static void _printTree(std::ostream& os, Node* node, int depth);

public:
	static void printTree(std::ostream& os, Node* node);
};

#endif