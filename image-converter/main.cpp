#include "OBJParser.h"
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
#include "RayTrace/Matrix4x4.h"
#include "RayTrace/RayTracer.h"
#include "RayTrace/KDTree/KDTree.h"

int main(int argc, char* argv[]) {
	try
	{
		/*ImageConverter* imageConverter = new ImageConverter(argc, argv);
		imageConverter->convertImage();*/

		ServiceContainer DI;
		DI.set<RayTracer>();

		ConsoleParser* consoleParser = ConsoleParser::GetInstance(argc, argv);
		DI.set<ConsoleParser*>(consoleParser);

		OBJParser* objParser = OBJParser::GetInstance("cow.obj");
		DI.set<OBJParser*>(std::move(objParser));
		
		KDTree* tree = new KDTree({ (*(DI.get<OBJParser*>()))->GetFaces().begin(), (*(DI.get<OBJParser*>()))->GetFaces().end() });
		DI.set<KDTree*>(std::move(tree));

		DI.set<std::vector<FigureI*>>((*(DI.get<OBJParser*>()))->GetFaces().begin(), (*(DI.get<OBJParser*>()))->GetFaces().end());

		std::vector<ILight*> lights;
		lights.push_back(new PointLight(Vector3D(1, 1, 1), 1, Vector3D(0, -10, -10)));
		lights.push_back(new PointLight(Vector3D(0, 1, 1), 1, Vector3D(0, 10, -10)));
		lights.push_back(new PointLight(Vector3D(1, 1, 1), 1, Vector3D(-1, 0, 1)));
		DI.set<std::vector<ILight*>>(lights);

		ICameraPositionProvider* camera = new StaticCameraPositionProvider();
		DI.set<ICameraPositionProvider*>(camera);

		Vector3D from(0, 7, -2) // From where camera look
			, to(0, 0, 0); // To where camera look

		Matrix4x4 camToWorld;
		camToWorld = camToWorld.lookAt(from, to);

		DI.set<Matrix4x4>(camToWorld);
		DI.set<IRayProvider*>(new PerspectiveRayProvider(DI.get<ICameraPositionProvider*>()[0]));

		DI.get<RayTracer>()->render(DI);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	

	return 0;
}