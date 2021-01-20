#pragma once

#include <functional>
#include <string.h>

#include "ScreenState.h"
#include "Camera.h"

class Screen
{
private:
    GLFWwindow *mWindow;

public:
    Screen(int width, int height);
    Screen() : Screen(1000, 600){};
    void run(std::function<void()> onCreate, std::function<void()> onDraw);

private:
    bool setupGLFW();
    bool setupGLEW();
    bool setupWindow();
    static void handleScreenChange(GLFWwindow *window, int width, int height);
    static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow *window, double xPos, double yPos);
};