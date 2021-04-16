#pragma once
#include <vector>
#include "../Vector3D.h"
#include "../Figure/Triangle.h"

struct Node
{
	Node();
	Node* left, * middle, * right;
	Node* SetFigures(const std::vector<Triangle*>& figures);

	std::vector<Triangle*> figures;
};

class KDTree
{
private:
	Node* root;

	float GetMedian(const std::vector<Triangle*>& figures, axis axis);
	axis GetAxis(int level);
	Node* BuildTree(const std::vector<Triangle*>& figures, int level);
	Node* SplitNode(Node* node, const std::vector<Triangle*>& figures, int level);
	std::tuple<std::vector<Triangle*>, std::vector<Triangle*>, std::vector<Triangle*>> GetBoundingGroups(const std::vector<Triangle*>& figures, axis axis, float split);
public:
	KDTree(const std::vector<Triangle*>& figures);
};

