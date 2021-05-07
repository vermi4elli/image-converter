#include "RayTracer.h"
#include "../ConsoleParser.h"
#include "../ImageWriterInterface/IImageWriter.h";
#include "RayProvider/PerspectiveRayProvider.h"
#include "Matrix4x4.h"

RGBAquad RayTracer::trace(Vector3D originray, Vector3D directionray, KDTree* tree, const std::vector<ILight*>& lights){
    
    float tNear = INFINITY;
    const FigureI* figure = NULL;
    intersectParams Params;
    std::vector<Triangle*> figures = tree->Intersection(tree->GetRoot(), originray, directionray);
    for (int i = 0; i < figures.size();i++) {
        float t0 = INFINITY, t1 = INFINITY;
        intersectParams temp;
        if (figures[i]->intersect(originray, directionray, temp, t0, t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < 0) continue;
            if (t0 < tNear) {
                tNear = t0;
                Params = temp;
                figure = figures[i];
            }
        }
    }

    if(!figure) return RGBAquad();
    Vector3D hitColor;
    for (int i = 0; i < lights.size(); i++) {
        Vector3D lightdir;
        Vector3D lightIntens;
        lights[i]->illuminate(Params.pHit, lightdir, lightIntens, tNear);
        lightdir = -lightdir;
        figures = tree->Intersection(tree->GetRoot(), Params.pHit, lightdir);
        bool shadowed = false;
        intersectParams temp;
        for (int j = 0; j < figures.size();j++) {
            float t0 = INFINITY, t1 = INFINITY;
            if (figure == figures[j]) continue;
            if (figures[j]->intersect(Params.pHit, lightdir, temp, t0, t1)) {
                if (t0 < 0) t0 = t1;
                if (t0 < 0) continue;
                shadowed = true;
                break;
            }
        }
        if(!shadowed) hitColor += (lightIntens * std::max(0.f, Params.hitNormal.dot(lightdir)));
    }
    hitColor = hitColor + 0.1;
    hitColor.one();
    hitColor = figure->surfaceColor * hitColor;
    return RGBAquad(hitColor.x*255, hitColor.y * 255, hitColor.z * 255);
};

void RayTracer::render(ServiceContainer& DI) {


    std::vector < std::vector <RGBAquad> > image;
    auto figures = DI.get<std::vector<FigureI*>>()[0];
    auto tree = DI.get<KDTree*>()[0];
    auto lights = DI.get<std::vector<ILight*>>()[0];
    auto camera = DI.get<ICameraPositionProvider*>()[0];
    auto rays = DI.get<IRayProvider*>()[0];
    auto camToWorld = DI.get<Matrix4x4>();
    auto originray = camera->getCameraPos();

    camToWorld->multVecMatrix(Vector3D(0), originray);
    int k = 0;
    image.resize(rays->height);
    for (unsigned y = 0; y < rays->height; ++y) {
        image[y].resize(rays->width);
        for (unsigned x = 0; x < rays->width; ++x) {
            Vector3D dir;
            camToWorld->multDirMatrix(Vector3D(rays->rays[k].x, rays->rays[k].y, rays->rays[k].z), dir);
            dir.normalize();
            image[y][x] = trace(originray, dir, tree, lights);
            k++;
        }
    }

    std::cout << "[Debug]: Done raytracing" << std::endl;
    
    std::unique_ptr<IImageWriter> w;
    w.reset(std::move(IImageWriter::createImageWriter(DI.get<ConsoleParser*>()[0]->goalImageType(), DI.get<ConsoleParser*>()[0]->pathOutput())));
    w.get()->write(image);
};