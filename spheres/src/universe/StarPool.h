#pragma once

#include "UniverseController.h"
#include "Star.h"
#include "render/InstancedMesh.h"
#include "render/Shader.h"
#include "shape/sphere/SphereGenerator.h"
#include "glcomponent/Camera.h"

struct StarGenAttr
{
    unsigned int size, quality;
    std::unique_ptr<AttributePayload> payload;
    std::unique_ptr<InstancedMesh> mesh;

    void create()
    {
        payload = std::make_unique<AttributePayload>();
        mesh = std::make_unique<InstancedMesh>();
    }

    void createMesh()
    {
        mesh->create(*payload.get());
        payload->release();
    }

    void recreateMesh()
    {
        mesh->recreateInstance(*payload.get());
        payload->release();
    }

    void drawMesh()
    {
        mesh->draw(*payload.get());
    }
};

class StarPool
{
private:
    const char *vShaderPath = "../res/shader/vInstanced.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    Shader shader;
    StarGenAttr hStars;
    StarGenAttr mStars;
    StarGenAttr lStars;
    float sphereAngle;
    bool isStarsRecreated = false;

    static void generateStars(StarGenAttr &starsAttr, SectorArray &activeSectors, long &offset);
    static void generateStarGenAttr(StarGenAttr &attr);
    static void generateStarInstancesMesh(StarGenAttr &attr, SectorArray &activeSectors, long &offset, long &count);
    static void generateStarInstancesTask(StarPool *sp);

public:
    bool pauseRecreation = false;
    
    StarPool();

    void create();
    void draw();
    void recreate();
};