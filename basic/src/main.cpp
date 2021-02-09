#define STB_IMAGE_IMPLEMENTATION

#include "screenview/Screen.h"
#include "scene/Scenes.h"
#include "assimp/Importer.hpp"

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
