#pragma once

struct InstanceAttr
{
    glm::vec4 color;
    glm::vec3 position;
    glm::mat4 model;

    void print()
    {
        std::cout << "InstanceAttr("
                  << "color:[" << color.x << ", " << color.y << ", " << color.z << ", " << color.w << "], "
                  << "position:[x:" << position.x << ", y:" << position.y << ", z:" << position.z << "], "
                  << "model:" << model.length << ")\n";
    }
};