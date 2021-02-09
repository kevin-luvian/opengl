#pragma once

#include "ScreenState.h"
#include "Camera.h"
#include "unit/Color.h"

class Screen
{
public:
    Screen(int width, int height);
    void run(std::function<void()> onCreate, std::function<void()> onDraw);

private:
    GLFWwindow *mWindow;

    bool setupGLFW();
    bool setupGLEW();
    bool setupWindow();
    static void handleScreenChange(GLFWwindow *window, int width, int height);
    static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow *window, double xPos, double yPos);
};