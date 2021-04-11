#pragma once
#include "../Vector3D.h"

class FigureI {
public:
	Vector3D surfaceColor;
	virtual ~FigureI() {};
	virtual bool intersect(Vector3D& originray, Vector3D& directionray, float& t0, float& t1) const = 0;
	virtual Vector3D getnormal(Vector3D& hitpoint) const = 0;
};