#include "RayTracer.h"
#include "BmpImageWriter.h";



RGBAquad RayTracer::trace(Vector3D originray, Vector3D directionray, const std::vector<FigureI*>& figures, const std::vector<PointLight>& lights){
    
    float tNear = INFINITY;
    const FigureI* figure = NULL;

    for (int i = 0; i < figures.size();i++) {
        float t0 = INFINITY, t1 = INFINITY;
        if (figures[i]->intersect(originray, directionray, t0, t1)) {
            if (t0 < 0) t0 = t1;
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
        lights[i].illuminate(phit, lightdir, tNear);
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
        if(!shadowed) hitColor += (lights[i].color * std::max(0.f, hitNormal.dot(lightdir_))) * lights[i].intensity;
    }
    hitColor.one();
    hitColor = figure->surfaceColor * hitColor;
    return RGBAquad(hitColor.x*255, hitColor.y * 255, hitColor.z * 255);
};

void RayTracer::render(const std::vector<FigureI*>& figures) {

    std::vector<PointLight> lights;
    lights.push_back(PointLight(Vector3D(1,1, 1),1, Vector3D(0, -10,-10)));
    //lights.push_back(PointLight(Vector3D(0, 1, 1), 1, Vector3D(0, 10, -10)));
    //lights.push_back(PointLight(Vector3D(1, 0.5, 0.5), 0.25, Vector3D(0, 0, 10)));
    std::vector < std::vector <RGBAquad> > image;
    unsigned width = 1920, height = 1080;
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 90, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);
    float dist = -1;
    Vector3D camera(0, 0, 0);

    image.resize(height);
    for (unsigned y = 0; y < height; ++y) {
        image[y].resize(width);
        for (unsigned x = 0; x < width; ++x) {
            float xx = (2 *((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2  * ((y + 0.5) * invHeight)) * angle;
            Vector3D raydir(xx, yy, dist);
            raydir.normalize();
            image[y][x] = trace(camera, raydir, figures, lights);
        }
    }

    BmpImageWriter w;

    w.write("raytrace.bmp", image);
};