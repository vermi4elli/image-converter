#pragma once
#include <vector>
#include <tuple>

#include "../Vector3D.h"
#include "../Figure/Triangle.h"
#include "../Figure/Cube.h"

struct Node
{
	Node(std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float>> borders);
	Node* left, * middle, * right;
	Node* SetFigures(const std::vector<Triangle*>& figures);
	Cube* boundingBox;

	std::vector<Triangle*> figures;
};

class KDTree
{
private:
	Node* root;

	std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float>> GetFiguresBorders(const std::vector<Triangle*>& figures);
	void CompareValuesByAxis(std::pair<float, float>& axisMinMax, const std::pair<float, float>& triangleMinMax);
	
	float GetMedian(const std::vector<Triangle*>& figures, axis axis);
	axis GetAxis(int level);
	Node* BuildTree(const std::vector<Triangle*>& figures, int level);
	Node* SplitNode(Node* node, const std::vector<Triangle*>& figures, int level);
	std::tuple<std::vector<Triangle*>, std::vector<Triangle*>, std::vector<Triangle*>> GetBoundingGroups(const std::vector<Triangle*>& figures, axis axis, float split);
public:
	KDTree(const std::vector<Triangle*>& figures);
	std::vector<Triangle*> Intersection(Node* node, Vector3D originray, Vector3D directionray);
	inline Node* GetRoot() { return root; };
};

