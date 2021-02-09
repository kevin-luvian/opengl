#define STB_IMAGE_IMPLEMENTATION

#include "glComponent/Screen.h"
#include "scene/HScene.h"

Scene01 scene01;

void onCreate()
{
    BENCHMARK_PROFILE();
    scene01.prepare();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    scene01.play();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen(800, 500);
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
