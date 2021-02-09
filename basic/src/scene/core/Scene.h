#pragma once

class Scene
{
public:
    virtual void prepare() = 0;
    virtual void play() = 0;

protected:
    Scene()
    {
        std::cout << "creating Scene\n";
    }
    virtual ~Scene() {}
};