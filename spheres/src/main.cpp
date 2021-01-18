#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/SpherePool.h"

static int TEST_SIZE = 5000;
static int TEST_COUNT = 50;

SpherePool pool(10000, 15);

void onCreate()
{
    BENCHMARK_PROFILE();
    pool.create();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    if (ScreenState::KeyState()[GLFW_KEY_0])
    {
        ScreenState::KeyState()[GLFW_KEY_0] = false;
        pool.recreateModels();
    }
    pool.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
