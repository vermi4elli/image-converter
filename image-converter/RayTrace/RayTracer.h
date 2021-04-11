#pragma once
#include <vector>
#include "Figure/FigureI.h"
#include "../DataTypes/rgbaquad.h"
#include "Figure/Sphere.h"
#include "Figure/Triangle.h"
#include "Figure/PointLight.h"

class RayTracer {
public:
	RGBAquad trace(Vector3D originray, Vector3D directionray,const std::vector<FigureI*>& figures, const std::vector<PointLight>& lights);
	void render(const std::vector<FigureI*>& figures);
};