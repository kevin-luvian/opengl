#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/icosphere/IcoSphere.h"
#include "shape/sphere/Sphere.h"

Pyramid p;
Sphere sp(100);
IcoSphere ico(5);

void onCreate()
{
    BENCHMARK_PROFILE();
    p.create();
    ico.create();
    ico.pos = glm::vec3(3.0, 0.0, 0.0);
    sp.create();
    sp.pos = glm::vec3(6.0, 0.0, 0.0);
}

void onDraw()
{
    BENCHMARK_PROFILE();
    p.update();
    p.draw();
    ico.draw();
    sp.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
