#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/icosphere/IcoSphere.h"
#include "random/simplexnoise/SimplexNoise.h"
#include "random/PerlinNoise.h"
#include "random/PerlinNoise2D.h"
#include "random/PerlinNoise3D.h"
#include "shape/sheet/Sheet.h"
#include "render/BufferConfig.h"
#include "light/Light.h"
#include "shape/VertexAttribute.h"

static const int sheetSize = 300;
Sheet sh(sheetSize, sheetSize);
IcoSphere ico(7);
Light ambientLight;

void onCreate()
{
    BENCHMARK_PROFILE();
    ico.createWThread();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    // sh.runWithNoiseThread();

    ico.create();
    ico.warpNoiseSpace();
    ico.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    RGEN::SuperSeed("a1234578");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
