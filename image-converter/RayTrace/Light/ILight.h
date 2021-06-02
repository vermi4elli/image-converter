#pragma once
#include "../Vector3D.h"

class ILight {
public:
	Vector3D color;
	float intensity;
	virtual void illuminate(const Vector3D& P, Vector3D& lightDir, Vector3D& lightIntensity, float& distance) const = 0;
};