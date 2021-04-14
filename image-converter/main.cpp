#include "ImageConverter.h"
#include "RayTrace/Figure/Cube.h"
#include "RayTrace/RayTracer.h"
#include "RayTrace/Figure/Triangle.h"
#include "RayTrace/Figure/MatrixTRS.h"
#include "RayTrace/Figure/Sphere.h"
#include "RayTrace/DI/ServiceContainer.h"
#include "RayTrace/Light/PointLight.h"
#include "RayTrace/Camera/StaticCameraPositionProvider.h"
#include "RayTrace/RayProvider/PerspectiveRayProvider.h"


int main(int argc, char* argv[]) {
	/*try
	{
		ImageConverter* imageConverter = new ImageConverter(argc, argv);
		imageConverter->convertImage();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}*/

	ServiceContainer DI;
	DI.set<RayTracer>();

	std::vector<FigureI*> figures;
	figures.push_back(new Sphere(Vector3D(1, 2, -20), 2, Vector3D(1, 0.5, 1)));
	figures.push_back(new Sphere(Vector3D(0, 2, -10), 0.5, Vector3D(1.00, 1, 1)));
	Vector3D v1(-1, -1, -5), v2(-3, -1, -10), v3(1, 5, -20);
	figures.push_back(new Triangle(v1, v2, v3, Vector3D(0.32, 1, 0.32)));
	//figures.push_back(new Cube(Vector3D(0.5, -1, -5), Vector3D(1.5,-2, -4), Vector3D(0.5, 1, 0.1)));
	//figures.push_back(new Triangle(Vector3D(-1, -1, -5), Vector3D(1, -1, -5), Vector3D(0, 1, -5), Vector3D(1, 1, 1)));

	DI.set<std::vector<FigureI*>>(figures);

	std::vector<ILight*> lights;
	lights.push_back(new PointLight(Vector3D(1, 1, 1), 1, Vector3D(0, -10, -10)));
	lights.push_back(new PointLight(Vector3D(0, 1, 1), 1, Vector3D(0, 10, -10)));
	//lights.push_back(new PointLight(Vector3D(1, 1, 1), 0.25, Vector3D(0, 0, 1)));
	DI.set<std::vector<ILight*>>(lights);


	ICameraPositionProvider* camera = new StaticCameraPositionProvider();
	DI.set<ICameraPositionProvider*>(camera);
	IRayProvider* prov = new PerspectiveRayProvider(DI.get<ICameraPositionProvider*>()[0]);
	DI.set<IRayProvider*>(prov);

	auto a = DI.get<std::vector<ILight*>>();
	DI.get<RayTracer>()->render(DI);

	return 0;
}