#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/icosahedron/Icosahedron.h"

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
Pyramid p2;
Icosahedron i;

void onCreate()
{
    BENCHMARK_PROFILE();
    p.create();
    p.mPos += glm::vec3(0.0f, 0.0f, -3.0f);
    // p2.create();
    i.create();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    p.update();
    // p2.update();

    p.draw();
    // p2.draw();

    i.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    std::thread(is_prime, 313222313).detach();
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
