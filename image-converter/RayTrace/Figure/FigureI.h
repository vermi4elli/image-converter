#pragma once
#include "MatrixTRS.h"

struct intersectParameters {
	intersectParameters(float tNear = 0, Vector3D pHit = Vector3D(0), Vector3D hitNormal = Vector3D(0)) 
		:tNear(tNear), pHit(pHit), hitNormal(hitNormal) {};
	float tNear;
	Vector3D pHit;
	Vector3D hitNormal;
};

constexpr float kEpsilon = 1e-8;
enum surfaceType {
	DEFAULT,
	REFLECT_AND_REFRACT,
	REFLECT,
	DIFFUSSE,
	DIFFUSSE_ADN_GLOSSY,
	SP
};
class FigureI {
public:
	surfaceType surfType = surfaceType::DEFAULT;
	float ior;
	Vector3D surfaceColor;
	virtual ~FigureI() {};
	virtual bool intersect(Vector3D& originray, Vector3D& directionray, intersectParameters& param,  float& t0, float& t1) const = 0;
	virtual void transform(MatrixTRS m) = 0;
};
struct Intersection {
	Intersection() {};
	Intersection(FigureI* figure, intersectParameters Params) :figure(figure), Params(Params){};
	intersectParameters Params;
	FigureI* figure;
	Vector3D hitColor;
};
