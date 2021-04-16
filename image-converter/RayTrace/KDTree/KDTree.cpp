#include <algorithm>
#include <tuple>
#include <iterator>
#include "KDTree.h"

constexpr int MaxLevel = 32;
constexpr int MinTrianglesAmount = 8;

Node::Node()
{
	this->left = nullptr;
	this->middle = nullptr;
	this->right = nullptr;
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

Node* KDTree::BuildTree(const std::vector<Triangle*>& figures, int level)
{
	Node* node = new Node();
	return (level >= MaxLevel || figures.size() <= MinTrianglesAmount) ? node->SetFigures(figures) : SplitNode(node, figures, level);
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