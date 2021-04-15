#pragma once
#include <vector>
#include "../Vector3D.h"
#include "../Figure/Triangle.h"

struct Node
{
	Node(const std::vector<Triangle*>& figures);
	Node* left, * middle, * right;

	std::vector<Triangle*> figures;
};

class KDTree
{
private:
	Node* root;

	float GetMedian(Node* node, axis axis);
	axis GetAxis(int level);
	Node* BuildTree(const std::vector<Triangle*>& figures, int level);
	Node* SplitNode(Node* node, int level);
	std::tuple<std::vector<Triangle*>, std::vector<Triangle*>, std::vector<Triangle*>> GetBoundingGroups(Node* node, axis axis, float split);
public:
	KDTree(const std::vector<Triangle*>& figures);
};

