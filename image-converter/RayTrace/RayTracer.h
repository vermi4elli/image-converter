#pragma once
#include <vector>
#include "Figure/FigureI.h"
#include "Light/ILight.h"
#include "../DataTypes/rgbaquad.h"
#include "DI/ServiceContainer.h"
#include "KDTree/KDTree.h"

class RayTracer {
	int MAXDEPTH = 5;
public:
	Intersection trace(Vector3D originray, Vector3D directionray, std::vector<FigureI*> figures);
	Intersection trace(Vector3D originray, Vector3D directionray, std::vector<Triangle*> figures);
	Vector3D shadowed(Intersection intersec, std::vector<FigureI*> figures, const std::vector<ILight*>& lights);
	Vector3D shadowed(Intersection intersec, KDTree* tree, const std::vector<ILight*>& lights);
	Vector3D traceWithTree(Vector3D originray, Vector3D directionray, KDTree* tree, const std::vector<ILight*>& lights);
	Vector3D traceWithoutTree(Vector3D originray, Vector3D directionray, std::vector<FigureI*> figures, const std::vector<ILight*>& lights);
	Vector3D whiteTrace(Vector3D originray, Vector3D directionray, std::vector<FigureI*> figures, const std::vector<ILight*>& lights, int depth);
	void render(ServiceContainer& DI);
};