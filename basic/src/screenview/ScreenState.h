#pragma once

class ScreenState
{
public:
    static ScreenState &GET()
    {
        static ScreenState instance;
        return instance;
    }

    static bool *KeyState() { return GET().keyState; }
    static void UpdateSize(unsigned int width, unsigned int height)
    {
        GET().mWidth = width;
        GET().mHeight = height;
    }
    static unsigned int Width() { return GET().mWidth; }
    static unsigned int Height() { return GET().mHeight; }

private:
    bool keyState[1024];
    unsigned int mWidth, mHeight;

    ScreenState() {}
};