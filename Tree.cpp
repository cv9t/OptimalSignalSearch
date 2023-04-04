#include "Tree.h"
#include "TreeUtils.h"
#include <queue>
#include <utility>

Tree::Tree(int depth)
{
	// TODO:
	// Сделать проверку на глубину дерева, depth > 1

	_depth = depth;
	_create();
}

Tree::~Tree()
{
	delete _root;
}

void Tree::_create()
{

}

//void Tree::_create(Node* parent, int depth)
//{
//	std::vector<std::pair<int, int>> values{ { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };
//
//	for (int i = 0; i < values.size(); i += 1) {
//		Node* child = new Node(values[i], parent);
//		parent->addChild(child);
//	}
//
//	if (depth > 1) {
//		for (int i = 0; i < values.size(); i += 1) {
//			_create(parent->getChild(i), depth - 1);
//		}
//	}
//}

Node* Tree::getRoot()
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, Tree& tree)
{
	TreeUtils::printTree(os, tree._root);
	return os;
}