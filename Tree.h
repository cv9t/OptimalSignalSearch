#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <fstream>

class Tree
{
private:
	int _depth;
	Node* _root = new Node({0, 0});

	void _create();

public:
	Tree(int depth);
	~Tree();

	Node* getRoot();

	friend std::ostream& operator<<(std::ostream& os, Tree& tree);
};

#endif TREE_H