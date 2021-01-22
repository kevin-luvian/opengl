#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/icosahedron/Icosahedron.h"
#include "shape/icosphere/IcoSphere.h"

bool is_prime(int x)
{
    BENCHMARK_PROFILE();
    std::cout << "Calculating. Please, wait...\n";
    for (int i = 2; i < x; ++i)
        if (x % i == 0)
            return false;
    std::cout << "Result is True!!\n";
    return true;
}

Pyramid p;
Icosahedron i;

static const int icps_count = 7;
IcoSphere icps[icps_count];


void onCreate()
{
    BENCHMARK_PROFILE();
    float z = -3.0f;
    for(int i = 0;i<icps_count;i++)
    {
        icps[i].mDepth = i;
        icps[i].create();
        icps[i].pos = glm::vec3(0.0f, 0.0f, z * i);
    }
    p.create();
    p.mPos += glm::vec3(-3.0f, 0.0f, 0.0f);
}

void onDraw()
{
    BENCHMARK_PROFILE();
    for(int i = 0;i<icps_count;i++)
    {
        icps[i].draw();
    }

    p.update();
    p.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
