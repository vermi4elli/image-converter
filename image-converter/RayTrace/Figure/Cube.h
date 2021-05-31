#pragma once
#include<iostream>
#include "../Vector3D.h"
#include "FigureI.h"


class Cube : public FigureI {
public:
	Vector3D bounds[2];
	Cube(const Vector3D& a, const Vector3D& b, const Vector3D& cs = Vector3D(0)) {

		bounds[0] = a;
		bounds[1] = b;
        surfaceColor = cs;
	}
    bool intersect(Vector3D& originray, Vector3D& directionray, intersectParameters& param, float& t0, float& t1) const
    {
        if (intersectCube(originray, directionray,t0,t1)) {
            float tNear = t0 < 0 ? t1 : t0;
            Vector3D pHit = originray + directionray * tNear;
            param = intersectParameters(
                tNear,
                pHit,
                getnormal(pHit)
            );
            return true;
        }
        return false;
    }


    bool intersect(Vector3D& originray, Vector3D& directionray, float& t0, float& t1) const
    {
        if (intersectCube(originray, directionray, t0, t1)) {
            return true;
        }
        return false;
    }
    bool intersectCube(Vector3D& originray, Vector3D& directionray, float& t0, float& t1) const
    {
        float tmin = (bounds[0].x - originray.x) / directionray.x;
        float tmax = (bounds[1].x - originray.x) / directionray.x;

        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (bounds[0].y - originray.y) / directionray.y;
        float tymax = (bounds[1].y - originray.y) / directionray.y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
            tmin = tymin;

        if (tymax < tmax)
            tmax = tymax;

        float tzmin = (bounds[0].z - originray.z) / directionray.z;
        float tzmax = (bounds[1].z - originray.z) / directionray.z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        if (tzmin > tmin)
            tmin = tzmin;

        if (tzmax < tmax)
            tmax = tzmax;
        t0 = tmin;
        t1 = tzmax;
        return true;
    }
    Vector3D getnormal(Vector3D& hitpoint)const {
        Vector3D center = Vector3D((bounds[0].x + bounds[1].x)*0.5, 
            (bounds[0].y + bounds[1].y) * 0.5,
            (bounds[0].z + bounds[1].z) * 0.5);
        Vector3D localPoint = hitpoint - center;
        Vector3D size = bounds[0] - center;
        float min = abs(size.x - abs(localPoint.x));
        Vector3D norm = Vector3D(1, 0, 0);
        norm = norm * (localPoint.x < 0 ? -1 : localPoint.x = 0 ? 0 : 1);
        float distance = abs(size.y - abs(localPoint.y));
        if (distance < min) {
            min = distance;
            norm = Vector3D(0, 1, 0);
            norm = norm * (localPoint.y < 0 ? -1 : localPoint.y = 0 ? 0 : 1);
        }
        distance = abs(size.z - abs(localPoint.z));
        if (distance < min) {
            min = distance;
            norm = Vector3D(0, 0, 1);
            norm = norm * (localPoint.z < 0 ? -1 : localPoint.z = 0 ? 0 : 1);
        }
        return norm;
    };
};