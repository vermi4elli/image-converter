#pragma once
#include "../Vector3D.h"
#include <vector>


class IRayProvider {
public:
	std::vector<Vector3D> rays;
	unsigned width, height;
	float fov;
	float dist;
	Vector3D camera;
	virtual std::vector<Vector3D> getRays() const = 0;
};