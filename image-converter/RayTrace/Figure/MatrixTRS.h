#pragma once
#include "../Vector3D.h"

class MatrixTRS {
	float matrix[4][4];
public:
	MatrixTRS(Vector3D translate, float rotation[3][3], Vector3D scale) {
		matrix[0][0] = rotation[0][0] * scale.x;
		matrix[0][1] = rotation[0][1];
		matrix[0][2] = rotation[0][2];
		matrix[0][3] = translate.x;
		matrix[1][0] = rotation[1][0];
		matrix[1][1] = rotation[1][1] * scale.y;
		matrix[1][2] = rotation[1][2];
		matrix[1][3] = translate.y;
		matrix[2][0] = rotation[2][0];
		matrix[2][1] = rotation[2][1];
		matrix[2][2] = rotation[2][2] * scale.z;
		matrix[2][3] = translate.z;
		matrix[3][0] = 0;
		matrix[3][1] = 0;
		matrix[3][2] = 0;
		matrix[3][3] = 1;
	};

	Vector3D& mult(Vector3D v) {
		Vector3D temp;
		temp.x = v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + 1 * matrix[0][3];
		temp.y = v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + 1 * matrix[1][3];
		temp.z = v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + 1 * matrix[2][3];
		return temp;
	};
};