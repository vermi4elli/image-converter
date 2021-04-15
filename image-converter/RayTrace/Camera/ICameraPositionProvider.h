#pragma once
#include "../Vector3D.h"

class ICameraPositionProvider {
	Vector3D cameraPos;
public:
	ICameraPositionProvider(Vector3D v = Vector3D(0)) : cameraPos(v) {};
	virtual Vector3D getCameraPos() const = 0;
};