#include "glcomponent/Screen.h"
#include "shape/sphere/icosphere/IcoSphere.h"
#include "random/simplexnoise/SimplexNoise.h"
#include "random/PerlinNoise.h"
#include "random/PerlinNoise2D.h"
#include "random/PerlinNoise3D.h"
#include "shape/sheet/Sheet.h"

static const int sheetSize = 360;
Sheet sh(sheetSize, sheetSize);
// IcoSphere ico(6);

void onCreate()
{
    BENCHMARK_PROFILE();
    // sh.createShape();
    // sh.warp();
    // sh.create();

    // ico.pos = glm::vec3(3.0f, 0.0f, 0.0f);
    // ico.createWThread();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    sh.runWithNoiseThread();
    // sh.draw();

    // ico.create();
    // ico.draw();
    // ico.warpNoiseSpace();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    RGEN::SuperSeed("a1234578");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
