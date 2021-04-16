#pragma once
#include <vector>
#include "Figure/FigureI.h"
#include "Light/ILight.h"
#include "../DataTypes/rgbaquad.h"
#include "DI/ServiceContainer.h"
#include "KDTree/KDTree.h"

class RayTracer {
public:
	RGBAquad trace(Vector3D originray, Vector3D directionray, KDTree* tree, const std::vector<ILight*>& lights);
	void render(ServiceContainer& DI);
};