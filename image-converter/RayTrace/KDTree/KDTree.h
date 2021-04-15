#pragma once
#include <vector>
#include "../Vector3D.h"
#include "../Figure/Triangle.h"

struct Node
{
	Node(const std::vector<Triangle*>& figures, Node* left, Node* right);
	Node* left, * right;

	std::vector<Triangle*> figures;
};

class KDTree
{
private:
	Node* root;

	std::tuple<int, int> GetMinMax(Node* node, axis axis);

public:
	void SplitNode(Node* node);
	KDTree(const std::vector<Triangle*>& figures);
};

