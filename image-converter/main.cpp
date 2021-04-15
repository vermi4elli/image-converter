#include "OBJParser.h"
#include "ImageConverter.h"
#include "RayTrace/Figure/Cube.h"
#include "RayTrace/RayTracer.h"
#include "RayTrace/Figure/Triangle.h"
#include "RayTrace/Figure/MatrixTRS.h"
#include "RayTrace/Figure/Sphere.h"

int main(int argc, char* argv[]) {
    /*try
    {
      std::unique_ptr<ImageConverter> imageConverter = std::make_unique<ImageConverter>(argc, argv);
      imageConverter.get()->convertImage();
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << std::endl;
      return -1;
    }*/

    OBJParser* objParser = OBJParser::GetInstance("cow.obj");

    std::vector<FigureI*> figures(objParser->GetFaces().begin(), objParser->GetFaces().end());
    RayTracer tracer;
    tracer.render(figures);

    /*figures.push_back(new Sphere(Vector3D(1, 2, -20), 2, Vector3D(1, 0.5, 1)));
    Vector3D v1(-1, -1, -5), v2(-3, -1, -10), v3(1, 5, -20);
    figures.push_back(new Triangle(v1, v2, v3, Vector3D(0.32, 1, 0.32)));
    RayTracer tracer;

    tracer.render(figures);*/
    return 0;
}