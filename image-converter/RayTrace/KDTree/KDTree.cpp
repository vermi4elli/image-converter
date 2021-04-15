#include "KDTree.h"

std::tuple<int, int> GetMinMax(Node* node, axis axis)
{
	int min = node->figures[0]->getMedianByAxis(axis), max = node->figures[0]->getMedianByAxis(axis);

	for (auto& figure : node->figures)
	{
		if (node->figures[0]->getMedianByAxis(axis) > max)
		{
			max = node->figures[0]->getMedianByAxis(axis);
		}
		else if (node->figures[0]->getMedianByAxis(axis) < min)
		{
			min = node->figures[0]->getMedianByAxis(axis);
		}
	}

	return std::make_pair(min, max);
}

void KDTree::SplitNode(Node* Node)
{
	std::tuple<int, int> xMinMax, yMinMax, zMinMax = 
}

KDTree::KDTree(const std::vector<Triangle*>& figures)
{
	root = new Node(figures, nullptr, nullptr);
}

Node::Node(const std::vector<Triangle*>& figures, Node* left, Node* right)
{
	this->figures = figures;
	this->left = left;
	this->right = right;
}
