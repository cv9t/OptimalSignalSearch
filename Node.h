#ifndef NODE_H
#define NODE_H

#include <vector>
#include <utility>
#include <fstream>

class Node
{
private:
	std::pair<int, int> _value;
	std::vector<Node*> _children;
	Node* _parent;

	int _getLevel(const Node* node, int level) const;

public:
	Node(const std::pair<int, int> value);
	Node(const std::pair<int, int> value, Node* parent);
	~Node();

	int getLevel() const;

	bool isRoot() const;

	bool isLeaf() const;

	std::pair<int, int> getValue() const;

	std::vector<Node*> getChildren() const;

	Node* getChild(int index) const;

	Node* getParent() const;

	void addChild(Node* node);

	void setParent(Node* parent);

	friend std::ostream& operator<<(std::ostream& os, Node& tree);
};

#endif NODE_H