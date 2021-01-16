#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/SpherePool.h"

Pyramid p;
SpherePool pool(5000, 25);

void onCreate()
{
    BENCHMARK_PROFILE();
    // p.create();

    pool.create();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    // p.update();
    // p.draw();

    // pool.update();
    pool.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
