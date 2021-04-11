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
	
    bool intersect(Vector3D& originray, Vector3D& directionray, float& t0, float& t1) const
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
        Vector3D temp = hitpoint;
        
        return temp;
    };
};