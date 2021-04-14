#pragma once
#include <vector>
#include "Figure/FigureI.h"
#include "Light/ILight.h"
#include "../DataTypes/rgbaquad.h"
#include "DI/ServiceContainer.h"

class RayTracer {
public:
	RGBAquad trace(Vector3D originray, Vector3D directionray,const std::vector<FigureI*>& figures, const std::vector<ILight*>& lights);
	void render(ServiceContainer& DI);
};