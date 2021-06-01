#pragma once
#include "../Vector3D.h"
#include <boost/qvm/mat_operations.hpp>

class MatrixTRS {
	float matrix[4][4], matrix_inv[4][4];
	Vector3D translate;
	Vector3D scale;
	float rotation[3][3] = { {1,0,0 }, {0, 1, 0 }, {0, 0, 1} };
public:
	MatrixTRS( float rotation_[3][3], Vector3D translate = Vector3D(0), Vector3D scale = Vector3D(1)): translate(translate), scale(scale){
		rotation[0][0] = rotation_[0][0];
		rotation[0][1] = rotation_[0][1];
		rotation[0][2] = rotation_[0][2];
		rotation[1][0] = rotation_[1][0];
		rotation[1][1] = rotation_[1][1];
		rotation[1][2] = rotation_[1][2];
		rotation[2][0] = rotation_[2][0];
		rotation[2][1] = rotation_[2][1];
		rotation[2][2] = rotation_[2][2];
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
		
		temp.x = v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + matrix[0][3];
		temp.y = v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + matrix[1][3];
		temp.z = v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + matrix[2][3];

		return temp;
	};
	Vector3D& multV(Vector3D v) {
		Vector3D temp;

		temp.x = v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2];
		temp.y = v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2];
		temp.z = v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2];

		return temp;
	};
	Vector3D& totranslate(Vector3D v) {
		Vector3D temp;

		temp.x = v.x + translate.x;
		temp.y = v.y + translate.y;
		temp.z = v.z + translate.z;

		return temp;
	};
	Vector3D& toscale(Vector3D v) {
		Vector3D temp;

		temp.x = v.x * scale.x;
		temp.y = v.y * scale.y;
		temp.z = v.z * scale.z;

		return temp;
	};
	Vector3D& torotate(Vector3D v) {
		Vector3D temp;
		temp.x = v.x * rotation[0][0] + v.y * rotation[0][1] + v.z * rotation[0][2];
		temp.y = v.x * rotation[1][0] + v.y * rotation[1][1] + v.z * rotation[1][2];
		temp.z = v.x * rotation[2][0] + v.y * rotation[2][1] + v.z * rotation[2][2];
		return temp;
	};
};