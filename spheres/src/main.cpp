#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/SpherePool.h"
#include "randoms/RGEN.h"
#include "universe/StarPool.h"
#include "universe/UniverseState.h"
#include "shape/icosphere/IcoSphereGenerator.h"
#include "shape/icosphere/Icosahedron.h"

static int TEST_SIZE = 5000;
static int TEST_COUNT = 50;

// SpherePool pool(4000, 15);
StarPool pool;
IcosahedronDrawer i;
Pyramid p;

void onCreate()
{
    BENCHMARK_PROFILE();
    std::cout << "Starcount " << UniverseState::TotalStarCount() << std::endl;

    pool.create();
    // p.create();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    if (ScreenState::KeyState()[GLFW_KEY_0])
    {
        ScreenState::KeyState()[GLFW_KEY_0] = false;
        pool.pauseRecreation = false;
        pool.recreate();
    }
    if (ScreenState::KeyState()[GLFW_KEY_9])
    {
        ScreenState::KeyState()[GLFW_KEY_9] = false;
        auto csector = Camera::CurrentSector();
        csector.print();
    }
    if (ScreenState::KeyState()[GLFW_KEY_P])
    {
        ScreenState::KeyState()[GLFW_KEY_P] = false;
        pool.pauseRecreation = !pool.pauseRecreation;
    }
    if (ScreenState::KeyState()[GLFW_KEY_M])
    {
        ScreenState::KeyState()[GLFW_KEY_M] = false;
        Camera::GET().autoMoveForward = !Camera::GET().autoMoveForward;
    }
    if (ScreenState::KeyState()[GLFW_KEY_UP])
    {
        ScreenState::KeyState()[GLFW_KEY_UP] = false;
        Camera::GET().moveSpeed += 500.0f;
    }
    if (ScreenState::KeyState()[GLFW_KEY_DOWN])
    {
        ScreenState::KeyState()[GLFW_KEY_DOWN] = false;
        Camera::GET().moveSpeed -= 500.0f;
    }
    if (Camera::OutOfNearViewSectorRange())
    {
        pool.recreate();
    }
    pool.draw();
    // p.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    RGEN::SuperSeed("abc");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}