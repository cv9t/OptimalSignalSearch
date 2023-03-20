#include "Node.h"

Node::Node(const std::pair<int, int> value)
{
	_value = value;
}

Node::Node(const std::pair<int, int> value, Node* parent) : Node(value)
{
	_parent = parent;
}

Node::~Node()
{
	_children.clear();
}

int Node::_getLevel(const Node* node, int level) const
{
	if (node->_parent == nullptr) return level;
	return _getLevel(node->_parent, level + 1);
}

int Node::getLevel() const
{
	return _getLevel(this, 0);
}

bool Node::isRoot() const
{
	return _parent == nullptr;
}

bool Node::isLeaf() const
{
	return _children.empty();
}

std::pair<int, int> Node::getValue() const
{
	return _value;
}

std::vector<Node*> Node::getChildren() const
{
	return _children;
}

Node* Node::getChild(int index) const
{
	// TODO:
	// Сделать проверку на index out of range, размер = 4

	return _children[index];
}

Node* Node::getParent() const
{
	return _parent;
}

void Node::addChild(Node* node)
{
	_children.push_back(node);
}

std::ostream& operator<<(std::ostream& os, Node& node)
{
	if (node.isRoot()) os << "*";
	else os << node._value.first << node._value.second;
	return os;
}