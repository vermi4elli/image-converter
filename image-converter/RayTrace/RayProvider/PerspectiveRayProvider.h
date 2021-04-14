#pragma once
#include "IRayProvider.h"

class PerspectiveRayProvider : public IRayProvider {
	void computeRays() {
		float invWidth = 1 / float(width), invHeight = 1 / float(height);
		float aspectratio = width / float(height);
		float angle = tan(M_PI * 0.5 * fov / 180.);
		rays.resize(height*width);
		int k = 0;
		for (unsigned y = 0; y < height; ++y) {
			for (unsigned x = 0; x < width; ++x) {
				float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
				float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
				rays[k] = Vector3D(xx, yy, dist).normalize();
				k++;
			}
		}
	}
public:
	PerspectiveRayProvider(ICameraPositionProvider* camera,
							int width = 1920,
							int height = 1280,
							float fov = 30,
							float dist = 1
							) {
		this->width = width;
		this->height = height;
		this->fov = fov;
		this->dist = camera->getCameraPos().z - dist;
		this->camera = camera;
		computeRays();
	}
	std::vector<Vector3D> getRays() const {
		return rays;
	};
};