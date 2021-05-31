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
    Triangle(Vector3D a, Vector3D b, Vector3D c, Vector3D sc = Vector3D(0), Vector3D normal_ = Vector3D(0)) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->surfaceColor = sc;
        if (normal_ != Vector3D(0)) normal = normal_;
        else {
            Vector3D edge1 = b - a;
            Vector3D edge2 = c - a;
            normal = edge1.crossprod(edge2);
        };
        median = Vector3D((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3, (a.z + b.z + c.z) / 3);
    };
    bool intersect(Vector3D& originray, Vector3D& directionray, intersectParameters& param, float& t0, float& t1) const;
    Triangle& operator +(Vector3D v);
    void setDotNormals(Vector3D norm1, Vector3D norm2, Vector3D norm3);
    Vector3D getnormal(Vector3D uv) const;
    float getMedianByAxis(axis axis);
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