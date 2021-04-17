#include "OBJParser.h"
#include "ConsoleParser.h"
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

constexpr int multZ = 3;
constexpr int multX = multZ * 3;
constexpr int multY = 0.5;

int main(int argc, char* argv[]) {
	try
	{
		/*ImageConverter* imageConverter = new ImageConverter(argc, argv);
		imageConverter->convertImage();*/

		ServiceContainer DI;
		DI.set<RayTracer>();

		ConsoleParser* consoleParser = ConsoleParser::GetInstance(argc, argv);
		DI.set<ConsoleParser*>(consoleParser);

		OBJParser* objParser = OBJParser::GetInstance((*(DI.get<ConsoleParser*>()))->pathSource());
		DI.set<OBJParser*>(std::move(objParser));
		
		KDTree* tree = new KDTree({ (*(DI.get<OBJParser*>()))->GetFaces().begin(), (*(DI.get<OBJParser*>()))->GetFaces().end() });
		DI.set<KDTree*>(std::move(tree));

		DI.set<std::vector<FigureI*>>((*(DI.get<OBJParser*>()))->GetFaces().begin(), (*(DI.get<OBJParser*>()))->GetFaces().end());

		ICameraPositionProvider* camera = new StaticCameraPositionProvider();
		DI.set<ICameraPositionProvider*>(camera);

		Vector3D min = DI.get<KDTree*>()[0]->GetRoot()->boundingBox->bounds[0];
		Vector3D max = DI.get<KDTree*>()[0]->GetRoot()->boundingBox->bounds[1];
		Vector3D from;
		switch (DI.get<ConsoleParser*>()[0]->modelSide())
		{
		case modelSide::FRONT:
			from = Vector3D(
				0,																					// x
				((max.y - min.y) < 1) ? 9 : ((max.y + min.y) / 2 + (max.y - min.y) * multY),		// y
				((max.z - min.z) < 1) ? -2 : -((max.z - min.z) * multZ)								// z
			);
			break;
		case modelSide::BACK:
			from = Vector3D(
				0,																					// x
				((max.y - min.y) < 1) ? 9 : ((max.y + min.y) / 2 + (max.y - min.y) * multY),		// y
				((max.z - min.z) < 1) ? 2 : ((max.z - min.z) * multZ)								// z
			);
			break;
		case modelSide::LEFT:
			from = Vector3D(
				((max.x - min.x) < 1) ? -2 : -((max.x - min.x) * multX),							// x
				((max.y - min.y) < 1) ? 9 : ((max.y + min.y) / 2 + (max.y - min.y) * multY),		// y
				0																					// z
			);
			break;
		case modelSide::RIGHT:
			from = Vector3D(
				((max.x - min.x) < 1) ? 2 : ((max.x - min.x) * multX),								// x
				((max.y - min.y) < 1) ? 9 : ((max.y + min.y) / 2 + (max.y - min.y) * multY),		// y
				0																					// z
			);
			break;
		default:
			break;
		}
		Vector3D to(
				(max.x + min.x) / 2,
				(max.y + min.y) / 2,
				(max.z + min.z) / 2
		);

		Matrix4x4 camToWorld;
		camToWorld = camToWorld.lookAt(from, to);
		DI.set<Matrix4x4>(camToWorld);

		std::vector<ILight*> lights;
		lights.push_back(new PointLight(Vector3D(1, 1, 1), 0.8, from + Vector3D(1, 1, 1)));
		DI.set<std::vector<ILight*>>(lights);

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