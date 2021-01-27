#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/icosphere/IcoSphere.h"
#include "shape/sphere/Sphere.h"
#include "shape/voxel/Cube.h"
#include "light/Light.h"
#include "render/material/Material.h"

Sphere sp(40);
IcoSphere ico(7);
Pyramid p;
Light light;
Cube c;

void onCreate()
{
    BENCHMARK_PROFILE();
    p.mPos = glm::vec3(0.0, -3.0, -7.0);
    p.create();

    ico.pos = glm::vec3(3.0, 0.0, -5.0);
    ico.create();

    sp.pos = glm::vec3(-3.0, 0.0, -3.0);
    sp.create();

    light.use(p.getShader());
    light.use(ico.getShader());
    light.use(sp.getShader());

    c.create();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    p.update();
    p.draw();

    ico.draw();

    sp.draw();

    c.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
