#include "RayTracer.h"
#include "../ImageWriterInterface/IImageWriter.h";
#include "RayProvider/PerspectiveRayProvider.h"
#include "Matrix4x4.h"
#include "../ConsoleParser.h"

RGBAquad RayTracer::trace(Vector3D originray, Vector3D directionray, const std::vector<FigureI*>& figures, const std::vector<ILight*>& lights){
    
    float tNear = INFINITY;
    const FigureI* figure = NULL;

    for (int i = 0; i < figures.size();i++) {
        float t0 = INFINITY, t1 = INFINITY;
        if (figures[i]->intersect(originray, directionray, t0, t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < 0) continue;
            if (t0 < tNear) {
                tNear = t0;
                figure = figures[i];
            }
        }
    }

    if(!figure)
    return RGBAquad();
    Vector3D hitColor;
    Vector3D phit = originray + directionray * tNear;
    Vector3D hitNormal = figure->getnormal(phit);
    hitNormal.normalize();
    for (int i = 0; i < lights.size(); i++) {
        Vector3D lightdir;
        lights[i]->illuminate(phit, lightdir, tNear);
        lightdir = -lightdir;
        bool shadowed = false;
        for (int j = 0; j < figures.size();j++) {
            float t0 = INFINITY, t1 = INFINITY;
            if (figure == figures[j]) continue;
            if (figures[j]->intersect(phit, lightdir, t0, t1)) {
                if (t0 < 0) t0 = t1;
                if (t0 < 0) continue;
                shadowed = true;
                break;
            }
        }
        if(!shadowed) hitColor += (lights[i]->color * std::max(0.f, hitNormal.dot(lightdir))) * lights[i]->intensity;
    }
    hitColor = hitColor + 0.1;
    hitColor.one();
    hitColor = figure->surfaceColor * hitColor;
    return RGBAquad(hitColor.x*255, hitColor.y * 255, hitColor.z * 255);
};

void RayTracer::render(ServiceContainer& DI) {

    
    std::vector < std::vector <RGBAquad> > image;
    auto figures = DI.get<std::vector<FigureI*>>()[0];
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
            image[y][x] = trace(originray, dir, figures, lights);
            k++;
        }
    }

    std::cout << "[Debug]: Done raytracing" << std::endl;
    
    std::unique_ptr<IImageWriter> w;
    w.reset(std::move(IImageWriter::createImageWriter((*(DI.get<ConsoleParser*>()))->goalImageType(), (*(DI.get<ConsoleParser*>()))->pathOutput())));
    w.get()->write(image);
};