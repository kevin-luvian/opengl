#pragma once

#include "StarPoolAttribute.h"
#include "render/Shader.h"
#include "shape/sphere/SphereGenerator.h"
#include "glcomponent/Camera.h"

class StarPool
{
private:
    const char *vShaderPath = "../res/shader/vInstanced3Transform.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    Shader shader;
    StarPoolAttribute hStars;
    StarPoolAttribute mStars;
    StarPoolAttribute lStars;
    float sphereAngle;
    bool isStarsRecreated = false;

    static void generateStars(StarPoolAttribute &starsAttr, DetailedArray<Sector> &activeSectors, long &offset);
    static void generateStarPoolAttribute(StarPoolAttribute &attr);
    static void generateStarPoolInstances(StarPoolAttribute &attr, DetailedArray<Sector> &activeSectors, long &offset, long &count);
    static void generateStarInstancesTask(StarPool *sp);

public:
    bool pauseRecreation = false;

    StarPool();

    void create();
    void draw();
    void recreate();
};