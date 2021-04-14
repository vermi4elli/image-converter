#pragma once
#include "../Vector3D.h"
#include <vector>
#include "../Camera/ICameraPositionProvider.h"

class IRayProvider {
public:
	std::vector<Vector3D> rays;
	int width, height;
	float fov;
	float dist;
	ICameraPositionProvider* camera;
	virtual std::vector<Vector3D> getRays() const = 0;
};