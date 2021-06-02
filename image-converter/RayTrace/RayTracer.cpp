#include "RayTracer.h"
#include "../ConsoleParser.h"
#include "../ImageWriterInterface/IImageWriter.h";
#include "RayProvider/PerspectiveRayProvider.h"
#include "Matrix4x4.h"
#include "../ImageWriterImplementations/PngImageWriter.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>    

Intersection RayTracer::trace(Vector3D originray, Vector3D directionray, std::vector<FigureI*> figures) {

    intersectParameters Params;
    FigureI* figure = NULL;
    float tNear = INFINITY;
    for (int i = 0; i < figures.size(); i++) {
        float t0 = INFINITY, t1 = INFINITY;
        intersectParameters temp;
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
    return Intersection(figure, Params);
};
Intersection RayTracer::trace(Vector3D originray, Vector3D directionray, std::vector<Triangle*> figures) {

    intersectParameters Params;
    FigureI* figure = NULL;
    float tNear = INFINITY;
    for (int i = 0; i < figures.size(); i++) {
        float t0 = INFINITY, t1 = INFINITY;
        intersectParameters temp;
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
    return Intersection(figure, Params);
};

Vector3D RayTracer::shadowed(Intersection intersec, std::vector<FigureI*> figures, const std::vector<ILight*>& lights) {
    Vector3D hitColor;
    for (int i = 0; i < lights.size(); i++) {
        Vector3D lightdir;
        Vector3D lightIntens;
        lights[i]->illuminate(intersec.Params.pHit, lightdir, lightIntens, intersec.Params.tNear);
        lightdir = -lightdir;
        bool shadowed = false;
        intersectParameters temp;
        for (int j = 0; j < figures.size(); j++) {
            float t0 = INFINITY, t1 = INFINITY;
            if (intersec.figure == figures[j]) continue;
            if (figures[j]->intersect(intersec.Params.pHit, lightdir, temp, t0, t1)) {
                if (t0 < 0) t0 = t1;
                if (t0 < 0) continue;
                shadowed = true;
                break;
            }
        }
        if (!shadowed) hitColor += (lightIntens * std::max(0.f, intersec.Params.hitNormal.dot(lightdir)));
    }
    return hitColor;
}
Vector3D RayTracer::shadowed(Intersection intersec, KDTree* tree, const std::vector<ILight*>& lights) {
    Vector3D hitColor;
    for (int i = 0; i < lights.size(); i++) {
        Vector3D lightdir;
        Vector3D lightIntens;
        lights[i]->illuminate(intersec.Params.pHit, lightdir, lightIntens, intersec.Params.tNear);
        lightdir = -lightdir;
        bool shadowed = false;
        intersectParameters temp;
        std::vector<Triangle*> figures = tree->Intersection(tree->GetRoot(), intersec.Params.pHit, lightdir);
        for (int j = 0; j < figures.size(); j++) {
            float t0 = INFINITY, t1 = INFINITY;
            if (intersec.figure == figures[j]) continue;
            if (figures[j]->intersect(intersec.Params.pHit, lightdir, temp, t0, t1)) {
                if (t0 < 0) t0 = t1;
                if (t0 < 0) continue;
                shadowed = true;
                break;
            }
        }
        if (!shadowed) hitColor += (lightIntens * std::max(0.f, intersec.Params.hitNormal.dot(lightdir)));
    }

    return hitColor;
}
Vector3D RayTracer::traceWithTree(Vector3D originray, Vector3D directionray, KDTree* tree, const std::vector<ILight*>& lights){
    

    std::vector<Triangle*> figures = tree->Intersection(tree->GetRoot(), originray, directionray);
    Intersection intersect = trace(originray, directionray, figures);

    if(!intersect.figure) return Vector3D(0);
    Vector3D hitColor = shadowed(intersect, tree, lights) + 0.1;
    hitColor.one();
    return intersect.figure->surfaceColor * hitColor;
};

Vector3D RayTracer::traceWithoutTree(Vector3D originray, Vector3D directionray, std::vector<FigureI*> figures, const std::vector<ILight*>& lights) {
    Intersection intersect = trace(originray, directionray, figures);
    if (!intersect.figure) return Vector3D(0);
    Vector3D hitColor = shadowed(intersect, figures, lights) + 0.1;
    hitColor.one();
    return intersect.figure->surfaceColor * hitColor;
}
Vector3D reflect(Vector3D vec, Vector3D normal) {
    return vec - normal * (2 * vec.dot(normal));
}
Vector3D refract(const Vector3D& I, const Vector3D& N, const float& ior)
{
    float cosi = std::clamp((float)-1, (float)1, I.dot(N));
    float etai = 1, etat = ior;
    Vector3D n = N;
    if (cosi < 0) { cosi = -cosi; }
    else { std::swap(etai, etat); n = -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? 0 : I * eta + n * (eta * cosi - sqrtf(k));
}
void fresnel(const Vector3D& I, const Vector3D& N, const float& ior, float& kr)
{
    float cosi = std::clamp((float)-1, (float)1, I.dot(N));
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }

    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));

    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }

}

Vector3D RayTracer::whittedTrace(Vector3D originray, Vector3D directionray, std::vector<FigureI*> figures, const std::vector<ILight*>& lights, int depth) {
    if(depth == 0)  return Vector3D(0);
    Intersection intersect = trace(originray, directionray, figures);
    if (!intersect.figure) return Vector3D(0);
    if (intersect.figure->surfType == surfaceType::REFLECT_AND_REFRACT) {
        float kr;
        fresnel(directionray, intersect.Params.hitNormal, intersect.figure->ior, kr);
        Vector3D reflectionDirection = reflect(directionray, intersect.Params.hitNormal);
        reflectionDirection.normalize();
        Vector3D refractionDirection = refract(directionray, intersect.Params.hitNormal, intersect.figure->ior);
        refractionDirection.normalize();
        Vector3D reflectionRayOrig = (intersect.Params.hitNormal.dot(reflectionDirection) < 0) ?
            intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
            intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
        Vector3D refractionRayOrig = (intersect.Params.hitNormal.dot(refractionDirection) < 0) ?
            intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
            intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
        Vector3D reflectionColor = whittedTrace(reflectionRayOrig, reflectionDirection, figures, lights, depth - 1);
        Vector3D refractionColor = whittedTrace(refractionRayOrig, refractionDirection, figures, lights, depth - 1);
        Vector3D hitColor = reflectionColor * kr + refractionColor * (1 - kr);
        return hitColor * intersect.figure->surfaceColor;
    } else
    if (intersect.figure->surfType == surfaceType::REFLECT) {
        float kr;
        fresnel(directionray, intersect.Params.hitNormal, intersect.figure->ior, kr);
        Vector3D reflectionDirection = reflect(directionray, intersect.Params.hitNormal);
        Vector3D reflectionRayOrig = (intersect.Params.hitNormal.dot(reflectionDirection) < 0) ?
            intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
            intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
        Vector3D hitColor = whittedTrace(reflectionRayOrig, reflectionDirection, figures, lights,depth - 1)* kr;
        return hitColor * intersect.figure->surfaceColor;
    }
    else
        if (intersect.figure->surfType == surfaceType::REFRACT) {

             float kr;
             fresnel(directionray, intersect.Params.hitNormal, intersect.figure->ior, kr);
             Vector3D refractionDirection = refract(directionray, intersect.Params.hitNormal, intersect.figure->ior);
             refractionDirection.normalize();
             Vector3D refractionRayOrig = (intersect.Params.hitNormal.dot(refractionDirection) < 0) ?
                 intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
                 intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
             Vector3D hitColor = whittedTrace(refractionRayOrig, refractionDirection, figures, lights, depth - 1) * (1 - kr);
             return hitColor * intersect.figure->surfaceColor;

        }
    else if (intersect.figure->surfType == surfaceType::DIFFUSSE) {


        Vector3D hitColor;
        hitColor += shadowed(intersect, figures, lights)* intersect.figure->surfaceColor / M_PI;
        Vector3D colorFromAnotherObj;
        int numOfRays = 8;
        for (int i = 0; i < numOfRays; i++) {
            Vector3D dir = Vector3D((rand() % 201 - 100), (rand() % 201 - 100), (rand() % 201 - 100));
            dir.normalize();
            if (dir.dot(intersect.Params.hitNormal) < 0) dir.x = -dir.x;
            if (dir.dot(intersect.Params.hitNormal) < 0) dir.y = -dir.y;
            if (dir.dot(intersect.Params.hitNormal) < 0) dir.z = -dir.z;
            float cos = std::max(0.f, intersect.Params.hitNormal.dot(dir));
            Vector3D c = whittedTrace(intersect.Params.pHit, dir, figures, lights, depth-1) * cos/ M_PI;
            colorFromAnotherObj += c;
        }
        hitColor += (colorFromAnotherObj / numOfRays);

        return hitColor;

    }
    else if (intersect.figure->surfType == surfaceType::DIFFUSSE_ADN_GLOSSY) {
        Vector3D hitColor;
        Vector3D lightAmt = 0, specularColor = 0;
        Vector3D shadowPointOrig = (intersect.Params.hitNormal.dot(directionray) < 0) ?
            intersect.Params.pHit + intersect.Params.hitNormal * 0.00001 :
            intersect.Params.pHit - intersect.Params.hitNormal * 0.00001;
            for (uint32_t i = 0; i < lights.size(); ++i) {
                Vector3D lightDir;
                Vector3D lightIntens;
                lights[i]->illuminate(intersect.Params.pHit, lightDir, lightIntens, intersect.Params.tNear);
                float lightDistance2 = lightDir.dot(lightDir);
                lightDir.normalize();
                float LdotN = std::max(0.f, lightDir.dot(intersect.Params.hitNormal));
                lightAmt = shadowed(intersect, figures, std::vector<ILight*>{lights[i]});
                Vector3D reflectionDirection = reflect(-lightDir, intersect.Params.hitNormal);
                specularColor += powf(std::max(0.f, reflectionDirection.dot(directionray)),25);
            }
        hitColor = lightAmt*0.8 + specularColor*0.2;

        return intersect.figure->surfaceColor*hitColor;
    }
    else if (intersect.figure->surfType == surfaceType::SP) {
        Vector3D hitColor;
        for (uint32_t i = 0; i < lights.size(); ++i) {
            Vector3D lightDir;
            Vector3D lightIntens;
            lights[i]->illuminate(intersect.Params.pHit, lightDir, lightIntens, intersect.Params.tNear);
            Vector3D vis = shadowed(intersect, figures, std::vector<ILight*>{lights[i]});
            float angle = (45 * M_PI / 180);
            float x = ((1 + atan2(intersect.Params.hitNormal.z, intersect.Params.hitNormal.x) / M_PI) * 0.5) * cos(angle);
            float y = (acosf(intersect.Params.hitNormal.y) / M_PI) * sin(angle);
            float s = x - y;
            float t = y + x;
            float scaleS = 20, scaleT = 20;
            float pattern = (s * scaleS - std::floor(s * scaleS)) < 0.5;
            hitColor += vis * pattern * std::max(0.f, intersect.Params.hitNormal.dot(-lightDir));
        }

        return intersect.figure->surfaceColor * hitColor;
    } else {
        Vector3D hitColor = (shadowed(intersect, figures, lights) + 0.1);
        hitColor.one();
        return intersect.figure->surfaceColor * hitColor;
    }
    
};
Vector3D RayTracer::whittedTraceWithTree(Vector3D originray, Vector3D directionray, KDTree* tree, const std::vector<ILight*>& lights, int depth) {
    std::vector<Triangle*> figures = tree->Intersection(tree->GetRoot(), originray, directionray);
    Intersection intersect = trace(originray, directionray, figures);
    if (depth == 0)  return Vector3D(0);
    if (!intersect.figure) return Vector3D(0);
    if (intersect.figure->surfType == surfaceType::REFLECT_AND_REFRACT) {
        float kr;
        fresnel(directionray, intersect.Params.hitNormal, intersect.figure->ior, kr);
        Vector3D reflectionDirection = reflect(directionray, intersect.Params.hitNormal);
        reflectionDirection.normalize();
        Vector3D refractionDirection = refract(directionray, intersect.Params.hitNormal, intersect.figure->ior);
        refractionDirection.normalize();
        Vector3D reflectionRayOrig = (intersect.Params.hitNormal.dot(reflectionDirection) < 0) ?
            intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
            intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
        Vector3D refractionRayOrig = (intersect.Params.hitNormal.dot(refractionDirection) < 0) ?
            intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
            intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
        Vector3D reflectionColor = whittedTraceWithTree(reflectionRayOrig, reflectionDirection, tree, lights, depth - 1);
        Vector3D refractionColor = whittedTraceWithTree(refractionRayOrig, refractionDirection, tree, lights, depth - 1);
        Vector3D hitColor = reflectionColor * kr + refractionColor * (1 - kr);
        return hitColor * intersect.figure->surfaceColor;
    }
    else
        if (intersect.figure->surfType == surfaceType::REFLECT) {
            float kr;
            fresnel(directionray, intersect.Params.hitNormal, intersect.figure->ior, kr);
            Vector3D reflectionDirection = reflect(directionray, intersect.Params.hitNormal);
            Vector3D reflectionRayOrig = (intersect.Params.hitNormal.dot(reflectionDirection) < 0) ?
                intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
                intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
            Vector3D hitColor = whittedTraceWithTree(reflectionRayOrig, reflectionDirection, tree, lights, depth - 1) * kr;
            return hitColor * intersect.figure->surfaceColor;
        }
        else
            if (intersect.figure->surfType == surfaceType::REFRACT) {

                float kr;
                fresnel(directionray, intersect.Params.hitNormal, intersect.figure->ior, kr);
                Vector3D refractionDirection = refract(directionray, intersect.Params.hitNormal, intersect.figure->ior);
                refractionDirection.normalize();
                Vector3D refractionRayOrig = (intersect.Params.hitNormal.dot(refractionDirection) < 0) ?
                    intersect.Params.pHit - intersect.Params.hitNormal * 0.00001 :
                    intersect.Params.pHit + intersect.Params.hitNormal * 0.00001;
                Vector3D hitColor = whittedTraceWithTree(refractionRayOrig, refractionDirection, tree, lights, depth - 1) * (1 - kr);
                return hitColor * intersect.figure->surfaceColor;

            }
            else if (intersect.figure->surfType == surfaceType::DIFFUSSE) {


                Vector3D hitColor;
                hitColor += shadowed(intersect, tree, lights) * intersect.figure->surfaceColor / M_PI;
                Vector3D colorFromAnotherObj;
                int numOfRays = 8;
                for (int i = 0; i < numOfRays; i++) {
                    Vector3D dir = Vector3D((rand() % 201 - 100), (rand() % 201 - 100), (rand() % 201 - 100));
                    dir.normalize();
                    if (dir.dot(intersect.Params.hitNormal) < 0) dir.x = -dir.x;
                    if (dir.dot(intersect.Params.hitNormal) < 0) dir.y = -dir.y;
                    if (dir.dot(intersect.Params.hitNormal) < 0) dir.z = -dir.z;
                    float cos = std::max(0.f, intersect.Params.hitNormal.dot(dir));
                    Vector3D c = whittedTraceWithTree(intersect.Params.pHit, dir, tree, lights, depth - 1) * cos / M_PI;
                    colorFromAnotherObj += c;
                }
                hitColor += (colorFromAnotherObj / numOfRays);

                return hitColor;

            }
            else if (intersect.figure->surfType == surfaceType::DIFFUSSE_ADN_GLOSSY) {
                Vector3D hitColor;
                Vector3D lightAmt = 0, specularColor = 0;
                Vector3D shadowPointOrig = (intersect.Params.hitNormal.dot(directionray) < 0) ?
                    intersect.Params.pHit + intersect.Params.hitNormal * 0.00001 :
                    intersect.Params.pHit - intersect.Params.hitNormal * 0.00001;
                for (uint32_t i = 0; i < lights.size(); ++i) {
                    Vector3D lightDir;
                    Vector3D lightIntens;
                    lights[i]->illuminate(intersect.Params.pHit, lightDir, lightIntens, intersect.Params.tNear);
                    float lightDistance2 = lightDir.dot(lightDir);
                    lightDir.normalize();
                    float LdotN = std::max(0.f, lightDir.dot(intersect.Params.hitNormal));
                    lightAmt = shadowed(intersect, tree, std::vector<ILight*>{lights[i]});
                    Vector3D reflectionDirection = reflect(-lightDir, intersect.Params.hitNormal);
                    specularColor += powf(std::max(0.f, reflectionDirection.dot(directionray)), 25);
                }
                hitColor = lightAmt * 0.8 + specularColor * 0.2;

                return intersect.figure->surfaceColor * hitColor;
            }
            else if (intersect.figure->surfType == surfaceType::SP) {
                Vector3D hitColor;
                for (uint32_t i = 0; i < lights.size(); ++i) {
                    Vector3D lightDir;
                    Vector3D lightIntens;
                    lights[i]->illuminate(intersect.Params.pHit, lightDir, lightIntens, intersect.Params.tNear);
                    Vector3D vis = shadowed(intersect, tree, std::vector<ILight*>{lights[i]});
                    float angle = (45 * M_PI / 180);
                    float x = ((1 + atan2(intersect.Params.hitNormal.z, intersect.Params.hitNormal.x) / M_PI) * 0.5) * cos(angle);
                    float y = (acosf(intersect.Params.hitNormal.y) / M_PI) * sin(angle);
                    float s = x - y;
                    float t = y + x;
                    float scaleS = 20, scaleT = 20;
                    float pattern = (s * scaleS - std::floor(s * scaleS)) < 0.5;
                    hitColor += vis * pattern * std::max(0.f, intersect.Params.hitNormal.dot(-lightDir));
                }

                return intersect.figure->surfaceColor * hitColor;
            }
            else {
                Vector3D hitColor = (shadowed(intersect, tree, lights) + 0.1);
                hitColor.one();
                return intersect.figure->surfaceColor * hitColor;
            }
};
void RayTracer::render(ServiceContainer& DI) {


    std::vector < std::vector <RGBAquad> > image;
    auto figures = DI.get<std::vector<FigureI*>>()[0];
    //auto tree = DI.get<KDTree*>()[0];
    auto lights = DI.get<std::vector<ILight*>>()[0];
    auto camera = DI.get<ICameraPositionProvider*>()[0];
    auto rays = DI.get<IRayProvider*>()[0];
    //auto camToWorld = DI.get<Matrix4x4>();
    auto originray = camera->getCameraPos();

    //camToWorld->multVecMatrix(Vector3D(0), originray);
    int k = 0;
    image.resize(rays->height);
    int percent = rays->height / 10;
    for (unsigned y = 0; y < rays->height; ++y) {
        image[y].resize(rays->width);
        if(y % percent == 0) std::cout << "[Debug]: Raytracing ready for :" << ((float)y/ (float)rays->height) * 100 << "%"<< std::endl;
        for (unsigned x = 0; x < rays->width; ++x) {
            Vector3D dir(rays->rays[k].x, rays->rays[k].y, rays->rays[k].z);
            //camToWorld->multDirMatrix(Vector3D(rays->rays[k].x, rays->rays[k].y, rays->rays[k].z), dir);
            dir.normalize();
            Vector3D pixel= whittedTrace(originray, dir, figures, lights,MAXDEPTH);
            pixel.one();
            image[y][x] = RGBAquad(pixel.x*255, pixel.y * 255 , pixel.z * 255 );
            k++;
        }
    }

    std::cout << "[Debug]: Done raytracing" << std::endl;
    
    //std::unique_ptr<IImageWriter> w;
    //w.reset(std::move(IImageWriter::createImageWriter(DI.get<ConsoleParser*>()[0]->goalImageType(), DI.get<ConsoleParser*>()[0]->pathOutput())));
    PngImageWriter w("render.png");
    w.write(image);
};