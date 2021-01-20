#pragma once

#include "render/InstanceAttr.h"

struct Star
{
    InstanceAttr attributes;

    void updatePos(float x, float y, float z)
    {
        attributes.position = glm::vec3(x, y, z);
    }

    void print()
    {
        attributes.print();
        std::cout << "\n";
    }
};

struct StarArray
{
    std::unique_ptr<Star[]> data;
    long size;

    void create(long count)
    {
        data = std::make_unique<Star[]>(count);
        size = count;
    }
};