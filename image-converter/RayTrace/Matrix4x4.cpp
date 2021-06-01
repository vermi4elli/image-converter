
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4() {};

Matrix4x4::Matrix4x4(float a, float b, float c, float d, float e, float f, float g, float h,
    float i, float j, float k, float l, float m, float n, float o, float p)
{
    matrix[0][0] = a;
    matrix[0][1] = b;
    matrix[0][2] = c;
    matrix[0][3] = d;
    matrix[1][0] = e;
    matrix[1][1] = f;
    matrix[1][2] = g;
    matrix[1][3] = h;
    matrix[2][0] = i;
    matrix[2][1] = j;
    matrix[2][2] = k;
    matrix[2][3] = l;
    matrix[3][0] = m;
    matrix[3][1] = n;
    matrix[3][2] = o;
    matrix[3][3] = p;
};
    const float* Matrix4x4::operator [] (uint8_t i) const { return matrix[i]; };
    float* Matrix4x4::operator [] (uint8_t i) { return matrix[i]; };
    Matrix4x4 Matrix4x4::operator * (const Matrix4x4& v) const
    {
        Matrix4x4 tmp;
        multiply(*this, v, tmp);

        return tmp;
    };

    void Matrix4x4::multiply(const Matrix4x4& a, const Matrix4x4& b, Matrix4x4& c)
    {
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
                    a[i][2] * b[2][j] + a[i][3] * b[3][j];
            }
        }
    };
    Matrix4x4 Matrix4x4::transposed() const
    {
        Matrix4x4 t;
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                t[i][j] = matrix[j][i];
            }
        }
        return t;
    };
    Matrix4x4& Matrix4x4::transpose()
    {
        Matrix4x4 tmp(matrix[0][0],
            matrix[1][0],
            matrix[2][0],
            matrix[3][0],
            matrix[0][1],
            matrix[1][1],
            matrix[2][1],
            matrix[3][1],
            matrix[0][2],
            matrix[1][2],
            matrix[2][2],
            matrix[3][2],
            matrix[0][3],
            matrix[1][3],
            matrix[2][3],
            matrix[3][3]);
        *this = tmp;
        return *this;
    };

    void Matrix4x4::multVecMatrix(const Vector3D& src, Vector3D& dst) const
    {
        float a, b, c, w;

        a = src[0] * matrix[0][0] + src[1] * matrix[1][0] + src[2] * matrix[2][0] + matrix[3][0];
        b = src[0] * matrix[0][1] + src[1] * matrix[1][1] + src[2] * matrix[2][1] + matrix[3][1];
        c = src[0] * matrix[0][2] + src[1] * matrix[1][2] + src[2] * matrix[2][2] + matrix[3][2];
        w = 1 / (src[0] * matrix[0][3] + src[1] * matrix[1][3] + src[2] * matrix[2][3] + matrix[3][3]);
        dst.x = a * w;
        dst.y = b * w;
        dst.z = c * w;
    };

    void Matrix4x4::multDirMatrix(const Vector3D& src, Vector3D& dst) const
    {
        float a, b, c;

        a = src[0] * matrix[0][0] + src[1] * matrix[1][0] + src[2] * matrix[2][0];
        b = src[0] * matrix[0][1] + src[1] * matrix[1][1] + src[2] * matrix[2][1];
        c = src[0] * matrix[0][2] + src[1] * matrix[1][2] + src[2] * matrix[2][2];

        dst.x = a;
        dst.y = b;
        dst.z = c;
    };
    Matrix4x4 Matrix4x4::lookAt(const Vector3D& from, const Vector3D& to, const Vector3D& tmp)
    {
        Vector3D forward = from - to;
        forward.normalize();
        Vector3D rand = tmp;
        rand.normalize();
        Vector3D right = rand.crossprod(forward);
        Vector3D up = forward.crossprod(right);

        Matrix4x4 camToWorld;

        camToWorld[0][0] = right.x;
        camToWorld[0][1] = right.y;
        camToWorld[0][2] = right.z;
        camToWorld[1][0] = up.x;
        camToWorld[1][1] = up.y;
        camToWorld[1][2] = up.z;
        camToWorld[2][0] = forward.x;
        camToWorld[2][1] = forward.y;
        camToWorld[2][2] = forward.z;

        camToWorld[3][0] = from.x;
        camToWorld[3][1] = from.y;
        camToWorld[3][2] = from.z;

        return camToWorld;
    };
