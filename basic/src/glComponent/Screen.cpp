#include "Screen.h"

Screen::Screen(int width, int height)
{
    ScreenState::UpdateSize(width, height);
    Camera::UpdateSize();
    bool *keys = ScreenState::KeyState();
    for (int i = 0; i < 1024; i++)
        keys[i] = false;
}

void Screen::run(std::function<void()> onCreate, std::function<void()> onDraw)
{
    if (!setupGLFW() || !setupWindow())
    {
        glfwTerminate();
        return;
    }

    if (!setupGLEW())
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        return;
    }

    // bind window with screen obj
    glfwSetWindowUserPointer(mWindow, this);

    // handle callbacks
    glfwSetFramebufferSizeCallback(mWindow, handleScreenChange);
    glfwSetKeyCallback(mWindow, handleKeys);
    glfwSetCursorPosCallback(mWindow, handleMouse);

    // create objects
    onCreate();

    // loop window
    Benchmark::Get().setCategory("render");
    while (!glfwWindowShouldClose(mWindow))
    {
        BENCHMARK_PROFILE_NAME("DRAW_LOOP");

        // handle user input
        glfwPollEvents();
        Camera::KeyUpdate();

        {
            BENCHMARK_PROFILE_NAME("CLEAR_WINDOW");
            unit::color col = Colors::BLACK;
            glClearColor(col.r, col.g, col.b, col.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        onDraw();
        {
            BENCHMARK_PROFILE_NAME("SWAP_BUFFERS");
            // swap drawing screen
            glfwSwapBuffers(mWindow);
        }
    }

    return;
}

bool Screen::setupGLFW()
{
    BENCHMARK_PROFILE();
    // initialize glfw
    if (!glfwInit())
    {
        printf("GLFW not initialized!\n");
        return false;
    }

    // setup glfw context ver: 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // setup glfw compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // removing vsync
    glfwSwapInterval(0);

    return true;
}
bool Screen::setupGLEW()
{
    BENCHMARK_PROFILE();
    // allow extensions
    glewExperimental = GL_TRUE;

    // initialize glew
    if (glewInit() != GLEW_OK)
    {
        printf("GLEW not initialized!\n");
        return false;
    }
    return true;
}
bool Screen::setupWindow()
{
    BENCHMARK_PROFILE();
    mWindow = glfwCreateWindow(ScreenState::Width(), ScreenState::Height(), "window", nullptr, nullptr);

    if (!mWindow)
    {
        printf("Window is not initialized!\n");
        return false;
    }

    int bufferWidth, bufferHeight;

    // get aspect ratio
    glfwGetFramebufferSize(mWindow, &bufferWidth, &bufferHeight);

    // set context glfw
    glfwMakeContextCurrent(mWindow);

    // enable culling
    if (ScreenState::IsCulled())
        glEnable(GL_CULL_FACE);

    // enable depth
    glEnable(GL_DEPTH_TEST);

    // enable MSAA
    glEnable(GL_MULTISAMPLE);

    // multisampling
    glfwWindowHint(GLFW_SAMPLES, 4);

    // opengl viewport
    glViewport(0, 0, bufferWidth, bufferHeight);

    // remove mouse cursor
    if (!ScreenState::IsCursorEnabled())
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

void Screen::handleScreenChange(GLFWwindow *window, int width, int height)
{
    Camera::UpdateSize();
    glViewport(0, 0, width, height);
}

void Screen::handleKeys(GLFWwindow *window, int key, int code, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        bool *keys = ScreenState::KeyState();
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Screen::handleMouse(GLFWwindow *window, double xPos, double yPos)
{
    Camera::MouseMove(xPos, yPos);
}