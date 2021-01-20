#include "glcomponent/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "shape/sphere/SpherePool.h"
#include "randoms/RGEN.h"
#include "universe/UniverseController.h"
#include "universe/StarPool.h"

static int TEST_SIZE = 5000;
static int TEST_COUNT = 50;

// SpherePool pool(4000, 15);
StarPool pool;

void onCreate()
{
    BENCHMARK_PROFILE();
    std::cout << "Starcount " << UniverseController::GET().StarCount << std::endl;

    pool.create();
    // auto sectors = UniverseController::SurroundingActiveSectors();
    // UniverseController::PrintSectors(sectors.get(), UniverseController::GET().StarCount);
}

void onDraw()
{
    BENCHMARK_PROFILE();
    if (ScreenState::KeyState()[GLFW_KEY_0])
    {
        ScreenState::KeyState()[GLFW_KEY_0] = false;
        pool.recreate();
    }
    if (ScreenState::KeyState()[GLFW_KEY_9])
    {
        ScreenState::KeyState()[GLFW_KEY_9] = false;
        auto csector = UniverseController::CameraSector();
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
        Camera::GET().moveSpeed += 30.0f;
    }
    if (ScreenState::KeyState()[GLFW_KEY_DOWN])
    {
        ScreenState::KeyState()[GLFW_KEY_DOWN] = false;
        Camera::GET().moveSpeed -= 30.0f;
    }
    if (UniverseController::IsCameraOutOfHighQualityRange())
    {
        pool.recreate();
    }
    pool.draw();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    RGEN::SuperSeed("abc");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();

    // long v = -14;
    // long div = 30;

    // auto test = util::DivideLong(v, div / 2);
    // std::cout << div / 2 << std::endl;
    // std::cout << test << std::endl;

    // uint32_t bound = 1;
    // auto sSectors = SectorGenerator::GenerateTopBottomSurroundingSectors(bound);
    // UniverseController::PrintSectors(sSectors.sectors.get(), sSectors.size);

    // auto sSectors = SectorGenerator::GenerateSurroundingActiveSectors({0, 0, 0}, 10, 150);
    // UniverseController::PrintSectors(sSectors.sectors.get(), sSectors.size);

    // RGEN::SuperSeed("1");
    // for (int i = 0; i < 10; i++)
    // {
    //     RGEN::Seed(i);
    //     std::cout << RGEN::Random() << std::endl;
    // }
    // std::cout << std::endl;
    // for (int i = 0; i < 10; i++)
    // {
    //     std::cout << RGEN::NoUpdateRandom(i) << std::endl;
    // }
}

// the pos
// gl_Position = viewProjection * (transform * model * vec4(vertex, 1.0) + vec4(position, 1.0));
// the other pos
// gl_Position = viewProjection * model * vec4(vertex, 1.0);