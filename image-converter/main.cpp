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
#include "RayTrace/Light/DirectionalLight.h"
#include "RayTrace/Figure/Plane.h"

constexpr int multZ = 3;
constexpr int multX = multZ * 3;
constexpr int multY = 0.5;

int main(int argc, char* argv[]) {
	try
	{
		srand(time(NULL));
		/*ImageConverter* imageConverter = new ImageConverter(argc, argv);
		imageConverter->convertImage();*/

		ServiceContainer DI;
		DI.set<RayTracer>();
		/*
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
		*/
		std::vector<FigureI*> figures;
		//Sphere* sp1 = new Sphere(Vector3D(2.5, 0, -10), 1, Vector3D(1, 1, 1));
		//sp1->surfType = surfaceType::REFLECT;
		//sp1->ior = 5;
		//figures.push_back(sp1);
		//figures.push_back(new Sphere(Vector3D(5, 0, -50), 5, Vector3D(1, 0.1, 0.1)));
		//Triangle* trig = new Triangle(Vector3D(0, 2, -1), Vector3D(-2.5, -2, 1), Vector3D(2.5, -2, 1), Vector3D(1, 1, 1));
		//trig->setDotNormals(Vector3D(0,-1 , 0.5).normalize(), Vector3D(0, 1, -0.5).normalize(), Vector3D(1, 1, -0.5).normalize());
		//float mat[3][3] = { {1,0,0 }, {0, 1, 0 }, {0, 0, 1} }; /*{
		//	{ 0.86602540378, 0,-0.5 },
		//	{0, 1,0 },
		//	{ 0.5, 0, 0.86602540378} };*/
		//MatrixTRS trs = MatrixTRS(mat,Vector3D(0,0,-20), Vector3D(1, 1,1));
		//trig->transform(trs);
		//figures.push_back(trig);
		figures.push_back(new Triangle(Vector3D(2.5, 0, -10), Vector3D(2.5, 0, -10), Vector3D(2.5, 0, -10), Vector3D(1, 0.1, 0.1)));
		Sphere* sp = new Sphere(Vector3D(-2.5, 0, -10), 1, Vector3D(1, 1,1));
		sp->surfType = surfaceType::DIFFUSSE;
		//sp->transform(trs);
		figures.push_back(sp);
		Sphere* sp1 = new Sphere(Vector3D(-0.5, 0, -10), 1, Vector3D(1, 0.1, 0.1));
		sp1->surfType = surfaceType::DIFFUSSE;
		sp1->ior = 1.5;
		figures.push_back(sp1);
		figures.push_back(new Plane());
		DI.set<std::vector<FigureI*>>(figures);
		ICameraPositionProvider* camera = new StaticCameraPositionProvider();
		DI.set<ICameraPositionProvider*>(camera);
		std::vector<ILight*> lights;
		//lights.push_back(new PointLight(Vector3D(1, 1, 1),800,  Vector3D(0,10,-10)));
		//lights.push_back(new PointLight(Vector3D(1, 1, 1), 800, Vector3D(-10, 10, -10)));
		lights.push_back(new DirectionalLight(Vector3D(1, 1, 1),0.5,Vector3D(0, 1, 0)));
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