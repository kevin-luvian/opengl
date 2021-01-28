#include "screenview/Screen.h"
#include "shape/pyramid/Pyramid.h"
#include "draw/shader/ShaderManager.h"
#include "draw/shader/ShaderClass.h"
#include "draw/shader/impl/SimpleShader.h"
#include "scene/MainScene.h"
#include "light/Light.h"

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
