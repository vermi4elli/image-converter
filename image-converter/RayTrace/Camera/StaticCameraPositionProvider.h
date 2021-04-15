#pragma once
#include "ICameraPositionProvider.h"

class StaticCameraPositionProvider: public ICameraPositionProvider{
public:
	Vector3D getCameraPos() const {
		return Vector3D(0,0,0);
	};
};