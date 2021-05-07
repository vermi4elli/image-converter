#pragma once
#include <tuple>
#include <cmath> 

#define M_PI 3.141592653589793 
#define INFINITY 1e8 

class Vector3D {
public:
    float x, y, z;
    Vector3D() : x(float(0)), y(float(0)), z(float(0)) {};
    Vector3D(float x) : x(float(x)),y(float(x)), z(float(x)) {};
    Vector3D(float x, float y, float z) : x(float(x)), y(float(y)), z(float(z)) {};
    Vector3D& normalize();
    Vector3D operator * (const float& f) const;
    Vector3D operator / (const float& f) const;
    Vector3D operator * (const Vector3D& v) const;
    float dot(const Vector3D& v) const;
    Vector3D crossprod(const Vector3D& v) const;
    Vector3D operator - (const Vector3D& v) const;
    Vector3D operator + (const Vector3D& v) const;
    Vector3D& operator += (const Vector3D& v);
    Vector3D& operator *= (const Vector3D& v);
    friend inline bool operator==(const Vector3D& lhs, const Vector3D& rhs) { return std::tie(lhs.x, lhs.y, lhs.z) == std::tie(rhs.x, rhs.y, rhs.z); };
    friend inline bool operator!=(const Vector3D& lhs, const Vector3D& rhs) { return !(lhs == rhs); }
    Vector3D operator - () const;
    float length2() const;
    float length() const;
    Vector3D& rotate(float fi);
    void one() {
        if (x > 1) x = 1;
        if (y > 1) y = 1;
        if (z > 1) z = 1;
    }
    const float& operator [] (int i) const { return (&x)[i]; }
    float& operator [] (int i) { return (&x)[i]; }
};
