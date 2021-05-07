#pragma once
#include<iostream>
#include "../Vector3D.h"
#include "FigureI.h"


class Plane : public FigureI {
public:
    Vector3D normal = Vector3D(0,-1,0);
    Vector3D pos = Vector3D(0);
    Plane() {};
    bool intersect(Vector3D& originray, Vector3D& directionray, intersectParams& param, float& t0, float& t1) const
    {
        float dot = normal.dot(directionray);
        if (dot > kEpsilon)
        {
            Vector3D dir = pos - originray;
            float t = dir.dot(normal) / dot;
            if (t >= 0)
            {
                t0 = t;
                param = intersectParams(
                    originray + directionray * t,
                    normal
                );
                return true;
            }
        }
        return false;
    }   
};