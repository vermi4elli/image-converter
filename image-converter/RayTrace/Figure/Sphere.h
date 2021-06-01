#pragma once
#include <cmath> 
#include "../Vector3D.h"
#include "FigureI.h"


class Sphere : public FigureI{
public:
    Vector3D center;                           /// position of the sphere 
    float radius, radius2;                  /// sphere radius and radius^2 

    Sphere(
        const Vector3D& c,
        const float& r,
        const Vector3D& sc) :
        center(c), radius(r), radius2(r* r){
        surfaceColor = sc;
    };
    void transform(MatrixTRS m) {
        center = m.totranslate(center);
        Vector3D v(1);
        v = m.toscale(v);

        radius *= v.x;

        radius2 = radius* radius;

    };
    bool intersect(Vector3D& originray, Vector3D& directionray, intersectParameters& param, float& t0, float& t1) const
    {
        Vector3D l = center - originray;
        float tca = l.dot(directionray);
        if (tca < 0) return false;
        float d2 = l.dot(l) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        t0 = tca - thc;
        t1 = tca + thc;
        float tNear = t0 < 0 ? t1 : t0;
        Vector3D phit = originray + directionray * tNear;
        param = intersectParameters(
                tNear,
                phit,
                getnormal(phit)
            );
        return true;
    }
    Vector3D getnormal(Vector3D& hitpoint) const {
        return hitpoint - center;
    }
};