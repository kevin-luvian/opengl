#pragma once

class Renderable
{
public:
    virtual void create() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

protected:
    virtual ~Renderable() {}
    Renderable()
    {
        std::cout << "creating renderable\n";
    }
};