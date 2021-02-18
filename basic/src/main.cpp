#define STB_IMAGE_IMPLEMENTATION

#include "glComponent/Screen.h"
#include "scene/HScene.h"

Scene02 scene02;

void onCreate()
{
    BENCHMARK_PROFILE();
    scene02.prepare();
}

void onDraw()
{
    BENCHMARK_PROFILE();
    scene02.play();
}

int main(int, char **)
{
    Benchmark::Get().begin("opengl");
    Screen screen(800, 500);
    screen.run(onCreate, onDraw);
    Benchmark::Get().end();
}
