#pragma once
#include <vector>
#include <string>
#include "RayTrace/Figure/Triangle.h"

class OBJParser
{
private:
	static OBJParser* objParser_;
	OBJParser(const std::string& inputPath);

	std::vector<Vector3D*> vertices;
	std::vector<Vector3D*> normals;
	std::vector<Vector3D*> vertice_normals;
	std::vector<Triangle*> faces;
public:
	OBJParser(OBJParser& other) = delete;
	OBJParser(OBJParser&& other) = default;
	void operator=(const OBJParser&) = delete;

	static OBJParser* GetInstance(const std::string& inputPath);

	void PrintInfo() const;
	const std::vector<Triangle*>& const GetFaces();
};