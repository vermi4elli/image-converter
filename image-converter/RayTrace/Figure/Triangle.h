#pragma once

#include <cmath> 
#include "../Vector3D.h"
#include "FigureI.h"

constexpr float kEpsilon = 1e-8;

class Triangle : public FigureI {
public:
	Vector3D a, b, c;
    Vector3D edge1, edge2;
    Vector3D normal;
	Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D sc = Vector3D(0), Vector3D normal_ = Vector3D(0)) : a(a), b(b), c(c){
        edge1 = b - a;
        edge2 = c - a;
        if (normal_ != Vector3D(0)) normal = normal_;
        else normal = edge1.crossprod(edge2);
        surfaceColor = sc;
    };
    bool intersect(Vector3D& originray, Vector3D& directionray, float& t0, float& t1) const
    {
        Vector3D h = directionray.crossprod(edge2);
        auto dotprod_a = edge1.dot(h);

        if (dotprod_a > -kEpsilon && dotprod_a < kEpsilon)
        {
            return false;
        }
        float f = 1 / dotprod_a;
        Vector3D s = originray - a;
        float u = f * s.dot(h);
        if (u < 0.0 || u > 1.0)
        {
            return false;
        }
        Vector3D q = s.crossprod(edge1);
        float v = f * directionray.dot(q);
        if (v < 0.0 || ((double)u + (double)v) > 1.0)
        {
            return false;
        }

        float t = f * edge2.dot(q);
        t0 = t;
        t1 = t;
        return true;
    }
    Triangle& operator +(Vector3D v) {
        a += v;
        b += v;
        c += v;
        edge1 = b - a;
        edge2 = c - a;
        return *this;
    }
    Vector3D getnormal(Vector3D& hitpoint) const {
        return edge1.crossprod(edge2);
    }
};