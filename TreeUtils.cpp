#include "TreeUtils.h"

void TreeUtils::_printTree(std::ostream& os, Node* node, int depth)
{
	if (node == nullptr) {
		return;
	}

	for (int i = 0; i < depth; i += 1) {
		os << "\t";
	}

	if (node->isRoot()) {
		os << "root - *" << std::endl;
	}
	else {
		os << node->getLevel() << " - " << *node << std::endl;
	}

	for (Node* child : node->getChildren()) {
		_printTree(os, child, depth + 1);
	}
}

void TreeUtils::printTree(std::ostream& os, Node* node) {
	_printTree(os, node, 0);
}