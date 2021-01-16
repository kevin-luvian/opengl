#include "glcomponent/Screen.h"
#include "shape/Pyramid.h"

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

void onCreate()
{
    BENCHMARK_PROFILE();
    p.create();
    p2.create();
    p2.mPos += glm::vec3(0.0f, 0.0f, -3.0f);
}

void onDraw()
{
    BENCHMARK_PROFILE();
    p.update();
    p2.update();

    p.draw();
    p2.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    std::thread(is_prime, 313222313).detach();
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
