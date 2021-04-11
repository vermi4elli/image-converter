#pragma once
#include "../Vector3D.h"

class PointLight {
public:
	Vector3D color;
	float intensity;
	Vector3D position;
	PointLight(Vector3D c, float i, Vector3D p) : color(c), intensity(i), position(p){};
    void illuminate(const Vector3D& P, Vector3D& lightDir, float& distance) const
    {
        lightDir = (P - position);
        float r2 = lightDir.length2();
        distance = sqrt(r2);
        lightDir.x /= distance, lightDir.y /= distance, lightDir.z /= distance;
    }

};