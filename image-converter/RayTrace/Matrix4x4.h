#pragma once
#include "Vector3D.h"
#include <iostream>

class Matrix4x4 {
	float matrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
public:
	Matrix4x4();
	Matrix4x4(float a, float b, float c, float d, float e, float f, float g, float h,
		float i, float j, float k, float l, float m, float n, float o, float p);
	const float* operator [] (uint8_t i) const;
	float* operator [] (uint8_t i);
	static void multiply(const Matrix4x4& a, const Matrix4x4& b, Matrix4x4& c);
	Matrix4x4 operator * (const Matrix4x4& v) const;
	Matrix4x4 transposed() const;
	Matrix4x4& transpose();
	void multVecMatrix(const Vector3D& src, Vector3D& dst) const;
	void multDirMatrix(const Vector3D& src, Vector3D& dst) const;
	Matrix4x4 lookAt(const Vector3D& from, const Vector3D& to, const Vector3D& tmp = Vector3D(0, 1, 0));
};