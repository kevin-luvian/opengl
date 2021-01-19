#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/SpherePool.h"
#include "randoms/RGEN.h"

static int TEST_SIZE = 5000;
static int TEST_COUNT = 50;

SpherePool pool(5, 15);

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
    RGEN::SuperSeed("1");
    RGEN::Seed("4");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}

// the pos
// gl_Position = viewProjection * (transform * model * vec4(vertex, 1.0) + vec4(position, 1.0));
// the other pos
// gl_Position = viewProjection * model * vec4(vertex, 1.0);