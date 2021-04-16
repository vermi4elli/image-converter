#include <algorithm>
#include <iterator>
#include "KDTree.h"

constexpr int MaxLevel = 32;
constexpr int MinTrianglesAmount = 8;

Node::Node(std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float>> borders)
{
	this->left = nullptr;
	this->middle = nullptr;
	this->right = nullptr;

	auto xMinMax = std::get<0>(borders);
	auto yMinMax = std::get<1>(borders);
	auto zMinMax = std::get<2>(borders);

	this->boundingBox = new Cube(Vector3D(xMinMax.first, yMinMax.first, zMinMax.first), Vector3D(xMinMax.second, yMinMax.second, zMinMax.second));
}

Node* Node::SetFigures(const std::vector<Triangle*>& figures)
{
	this->figures = figures;
	return this;
}

KDTree::KDTree(const std::vector<Triangle*>& figures)
{
	root = BuildTree(figures, 0);
}

std::vector<Triangle*> KDTree::Intersection(Node* node, Vector3D originray, Vector3D directionray)
{
	if (node->left == nullptr && node->middle == nullptr && node->right == nullptr)
	{
		return node->figures;
	}

	float t0 = INFINITY, t1 = INFINITY;
	if (node->boundingBox->intersect(originray, directionray, t0, t1))
	{
		auto leftIntersects = Intersection(node->left, originray, directionray);
		auto rightIntersects = Intersection(node->right, originray, directionray);
		//auto middleIntersects = Intersection(node->middle, originray, directionray);
		leftIntersects.insert(leftIntersects.end(), rightIntersects.begin(), rightIntersects.end());
		return leftIntersects;
	}
	return node->figures;
}

Node* KDTree::BuildTree(const std::vector<Triangle*>& figures, int level)
{
	Node* node = new Node(GetFiguresBorders(figures));
	return (level >= MaxLevel || figures.size() <= MinTrianglesAmount) ? node->SetFigures(figures) : SplitNode(node, figures, level);
}

std::tuple<std::pair<float, float>, std::pair<float, float>, std::pair<float, float>> KDTree::GetFiguresBorders(const std::vector<Triangle*>& figures)
{
	if (figures.empty()) return std::make_tuple(std::pair<float, float>(), std::pair<float, float>(), std::pair<float, float>());

	std::pair<float, float> xMinMax{ figures[0]->a.x, figures[0]->a.x };
	std::pair<float, float> yMinMax{ figures[0]->a.y, figures[0]->a.y };
	std::pair<float, float> zMinMax{ figures[0]->a.z, figures[0]->a.z };

	for (auto& element : figures)
	{
		CompareValuesByAxis(xMinMax, element->getMinMaxByAxis(axis::X));
		CompareValuesByAxis(yMinMax, element->getMinMaxByAxis(axis::Y));
		CompareValuesByAxis(zMinMax, element->getMinMaxByAxis(axis::Z));
	}

	return std::make_tuple(xMinMax, yMinMax, zMinMax);
}

void KDTree::CompareValuesByAxis(std::pair<float, float>& axisMinMax, const std::pair<float, float>& triangleMinMax)
{
	if (axisMinMax.first > triangleMinMax.first) axisMinMax.first = triangleMinMax.first;
	if (axisMinMax.second < triangleMinMax.second) axisMinMax.second = triangleMinMax.second;
}

Node* KDTree::SplitNode(Node* node, const std::vector<Triangle*>& figures, int level)
{
	axis axis = GetAxis(level);
	float split = GetMedian(figures, axis);

	auto boundingGroups = GetBoundingGroups(figures, axis, split);

	// if all triangles are in the middle group - return
	if (std::get<1>(boundingGroups).size() == figures.size())
	{
		return node->SetFigures(figures);
	}

	node->left = BuildTree(std::get<0>(boundingGroups), level + 1);
	node->middle = BuildTree(std::get<1>(boundingGroups), level + 1);
	node->right = BuildTree(std::get<2>(boundingGroups), level + 1);
	return node;
}

axis KDTree::GetAxis(int level)
{
	return level % 3 == 0 ? axis::X : level % 3 == 1 ? axis::Y : axis::Z;
}

float KDTree::GetMedian(const std::vector<Triangle*>& figures, axis axis)
{
	if (figures.size() <= 2)
	{
		return 1;
	}

	// sorting the triangles by median triangle coordinate of the chosen axis
	std::vector<Triangle*> sortedFigures(figures.begin(), figures.end());
	std::sort(sortedFigures.begin(), sortedFigures.end(), [axis](auto l, auto r) {
		return l->getMedianByAxis(axis) < r->getMedianByAxis(axis);
		}
	);

	// getting the median float value of the split
	int index = (sortedFigures.size() - 1) / 2;
	return (sortedFigures.size() % 2 == 0) ? (sortedFigures[index]->getMedianByAxis(axis) + sortedFigures[index + 1]->getMedianByAxis(axis)) * 0.5f :
		sortedFigures[index]->getMedianByAxis(axis);
}

std::tuple<std::vector<Triangle*>, std::vector<Triangle*>, std::vector<Triangle*>> KDTree::GetBoundingGroups(const std::vector<Triangle*>& figures, axis axis, float split)
{
	std::vector<Triangle*> left, middle, right;

	std::copy_if(figures.begin(), figures.end(), std::back_inserter(left), [axis, split](auto i) {
		return i->getMedianByAxis(axis) < split;
		}
	);
	std::copy_if(figures.begin(), figures.end(), std::back_inserter(right), [axis, split](auto i) {
		return i->getMedianByAxis(axis) >= split;
		}
	);
	std::copy_if(figures.begin(), figures.end(), std::back_inserter(middle), [left, right](auto i) {
		return std::find(left.begin(), left.end(), i) == left.end() && std::find(right.begin(), right.end(), i) == right.end();
		}
	);

	return std::make_tuple(left, middle, right);
}
