#include "Vector3D.h"

Vector3D& Vector3D::normalize()
{
    float nor2 = length2();
    if (nor2 > 0) {
        float invNor = 1 / sqrt(nor2);
        x *= invNor, y *= invNor, z *= invNor;
    }
    return *this;
};
Vector3D Vector3D::operator * (const float& f) const { return Vector3D(x * f, y * f, z * f); };
Vector3D Vector3D::operator * (const Vector3D& v) const { return Vector3D(x * v.x, y * v.y, z * v.z); };
float Vector3D::dot(const Vector3D& v) const { return x * v.x + y * v.y + z * v.z; };
Vector3D Vector3D::crossprod(const Vector3D& v) const {
    return Vector3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
};
Vector3D Vector3D::operator - (const Vector3D& v) const { return Vector3D(x - v.x, y - v.y, z - v.z); };
Vector3D Vector3D::operator + (const Vector3D& v) const { return Vector3D(x + v.x, y + v.y, z + v.z); };
Vector3D& Vector3D::operator += (const Vector3D& v) { x += v.x, y += v.y, z += v.z; return *this; };
Vector3D& Vector3D::operator *= (const Vector3D& v) { x *= v.x, y *= v.y, z *= v.z; return *this; };
Vector3D Vector3D::operator - () const { return Vector3D(-x, -y, -z); };
float Vector3D::length2() const { return x * x + y * y + z * z; };
float Vector3D::length() const { return sqrt(length2()); };

Vector3D& Vector3D::rotate(float fi) {
    float sn = sin(fi* M_PI/180);
    float cs = cos(fi * M_PI / 180);
    float xx = cs * x - y * sn;
    float yy = sn * x + y * cs;
    x = xx;
    y = yy;
    return *this;
}