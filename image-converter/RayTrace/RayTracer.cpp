#include "RayTracer.h"
#include "../ImageWriterImplementations/PngImageWriter.h";
#include "./Light/PointLight.h"
#include "./RayProvider/PerspectiveRayProvider.h"

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
        Vector3D lightdir_ = -lightdir;
        bool shadowed = false;
        for (int j = 0; j < figures.size();j++) {
            float t0 = INFINITY, t1 = INFINITY;
            if (figure == figures[j]) continue;
            if (figures[j]->intersect(phit, lightdir_, t0, t1)) {
                if (t0 < 0) t0 = t1;
                if (t0 < 0) continue;
                shadowed = true;
                break;
            }
        }
        if(!shadowed) hitColor += (lights[i]->color * std::max(0.f, hitNormal.dot(lightdir_))) * lights[i]->intensity;
    }
    hitColor.one();
    hitColor = figure->surfaceColor * hitColor;
    return RGBAquad(hitColor.x*255, hitColor.y * 255, hitColor.z * 255);
};

void RayTracer::render(const std::vector<FigureI*>& figures) {

    std::vector<ILight*> lights;
    lights.push_back(new PointLight(Vector3D(1,1, 1),1, Vector3D(0, -10,-10)));
    lights.push_back(new PointLight(Vector3D(0, 1, 1), 1, Vector3D(0, 10, -10)));
    //lights.push_back(new PointLight(Vector3D(1, 1, 1), 0.25, Vector3D(0, 0, 1)));
    std::vector < std::vector <RGBAquad> > image;
    Vector3D camera(0, 0, 0);
    PerspectiveRayProvider rays;
    int k = 0;
    image.resize(rays.height);
    for (unsigned y = 0; y < rays.height; ++y) {
        image[y].resize(rays.width);
        for (unsigned x = 0; x < rays.width; ++x) {
            image[y][x] = trace(camera, rays.rays[k], figures, lights);
            k++;
        }
    }

    PngImageWriter w("raytrace.png");

    w.write(image);
};