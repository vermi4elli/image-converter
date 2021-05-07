#pragma once
#include "ILight.h"


class DirectionalLight : public ILight {
public:

    Vector3D dir;
    DirectionalLight(Vector3D c, float i,Vector3D dir) : dir(dir) {
        color = c;
        intensity = i;
        dir.normalize();
    };
    void illuminate(const Vector3D& P, Vector3D& lightDir, Vector3D& lightIntensity, float& distance) const
    {
        lightDir = -dir;
        lightIntensity = color * intensity;
        distance = INFINITY;
    }

};
