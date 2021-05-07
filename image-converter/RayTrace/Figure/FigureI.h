#pragma once
#include "../Vector3D.h"
struct intersectParams {
	intersectParams(Vector3D pHit = Vector3D(0), Vector3D hitNormal = Vector3D(0)) : pHit(pHit), hitNormal(hitNormal){};
	Vector3D pHit;
	Vector3D hitNormal;
};

constexpr float kEpsilon = 1e-8;

class FigureI {
public:
	Vector3D surfaceColor;
	virtual ~FigureI() {};
	virtual bool intersect(Vector3D& originray, Vector3D& directionray, intersectParams& param,  float& t0, float& t1) const = 0;
};