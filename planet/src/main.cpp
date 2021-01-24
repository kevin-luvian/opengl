#include "glcomponent/Screen.h"
#include "shape/sphere/icosphere/IcoSphere.h"
#include "random/simplexnoise/SimplexNoise.h"
#include "random/PerlinNoise.h"
#include "random/PerlinNoise2D.h"
#include "random/PerlinNoise3D.h"
#include "shape/sheet/Sheet.h"

Sheet sh(360, 360);
IcoSphere ico(5);

void onCreate()
{
    BENCHMARK_PROFILE();
    // sh.create();

    // ico.pos = glm::vec3(3.0f, 0.0f, 0.0f);
    ico.createWThread();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    // sh.draw();

    ico.create();
    ico.warpNoiseSpace();
    ico.draw();
}

void shuffle(DetailedArray<int> &table, unsigned int boundary)
{
    unsigned int i2;
    for (unsigned int i = 0; i < boundary; i++)
    {
        i2 = RGEN::Uint(0, boundary);
        table.swap(i, i2);
    }
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    RGEN::SuperSeed("a1234578");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();

    // DetailedArray<int> P;
    // P.make_empty(256);
    // for (int i = 0; i < 256; i++)
    // {
    //     P[i] = i;
    // }
    // for (int i = 0; i < 1000; i++)
    // {
    //     shuffle(P, 256);
    // }
    // for (int i = 0; i < 256; i++)
    // {
    //     std::cout << P[i] << ", ";
    //     if (((i + 1) & 15) == 0)
    //         std::cout << std::endl;
    // }
    // std::cout << std::endl;
}
