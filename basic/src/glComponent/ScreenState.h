#pragma once

class ScreenState
{
private:
    bool showCursor = true;
    bool faceCulling = false;
    bool keyState[1024];
    unsigned int mWidth, mHeight;

    ScreenState() {}
    ~ScreenState() {}
    static ScreenState &GET()
    {
        static ScreenState instance;
        return instance;
    }

public:
    static bool IsCursorEnabled() { return GET().showCursor; }
    static bool IsCulled() { return GET().faceCulling; }
    static bool *KeyState() { return GET().keyState; }
    static bool KeyState(unsigned int index) { return GET().keyState[index]; }
    static void UpdateSize(unsigned int width, unsigned int height)
    {
        GET().mWidth = width;
        GET().mHeight = height;
    }
    static unsigned int Width() { return GET().mWidth; }
    static unsigned int Height() { return GET().mHeight; }
};