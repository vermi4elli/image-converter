#pragma once

#include <cmath>
#include "../Vector3D.h"
#include "FigureI.h"

enum class axis
{
    X,
    Y,
    Z
};



class Triangle : public FigureI {
public:
	Vector3D a, b, c;
    Vector3D a_norm, b_norm, c_norm;
    Vector3D normal;
    bool dotNormals = false;
    Vector3D median;
	Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D sc = Vector3D(0), Vector3D normal_ = Vector3D(0)) : a(a), b(b), c(c){
        if (normal_ == Vector3D(0)) {
            Vector3D edge1 = b - a;
            Vector3D edge2 = c - a;
            normal = edge1.crossprod(edge2);
        }
        else
        {
            normal = normal_;
        }
        surfaceColor = sc;
        median = Vector3D((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3, (a.z + b.z + c.z) / 3);
    };
    bool intersect(Vector3D& originray, Vector3D& directionray, intersectParams& param, float& t0, float& t1) const
    {
        Vector3D edge1 = b - a;
        Vector3D edge2 = c - a;
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
        param = intersectParams(
            (originray + directionray * t),
            getnormal(Vector3D(u,v,0))
            );
        return true;
    }
    Triangle& operator +(Vector3D v) {
        a += v;
        b += v;
        c += v;
        return *this;
    }
    void setDotNormals(Vector3D norm1, Vector3D norm2, Vector3D norm3) {
        a_norm = norm1;
        b_norm = norm2;
        c_norm = norm3;
        dotNormals = true;

    }
    Vector3D getnormal(Vector3D uv) const {
        if (dotNormals) {
            return a_norm * (1 - uv.x - uv.y) + b_norm * uv.x + c_norm * uv.y ;
        }
        else {
            return normal;
        }
    }
    float getMedianByAxis(axis axis) {
        switch (axis)
        {
        case axis::X:
            return this->median.x;
            break;
        case axis::Y:
            return this->median.y;
            break;
        case axis::Z:
            return this->median.z;
            break;
        }
    };
    std::pair<float, float> getMinMaxByAxis(axis axis) {
        float v1, v2, v3, min, max;
        
        switch (axis)
        {
        case axis::X:
            v1 = this->a.x;
            v2 = this->b.x;
            v3 = this->c.x;
            break;
        case axis::Y:
            v1 = this->a.y;
            v2 = this->b.y;
            v3 = this->c.y;
            break;
        case axis::Z:
            v1 = this->a.z;
            v2 = this->b.z;
            v3 = this->c.z;
            break;
        }

        min = std::min({ v1, v2, v3 });
        max = std::max({ v1, v2, v3 });

        return std::pair<float, float>(min, max);
    }
};