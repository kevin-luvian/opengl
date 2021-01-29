#include "screenview/Screen.h"
#include "scene/MainScene.h"
#include "light/impl/PointLight.h"

MainScene scene;

void onCreate()
{
    BENCHMARK_PROFILE();
    scene.prepare();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    scene.play();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen;
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
