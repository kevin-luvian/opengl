#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "ScreenState.h"

class Camera
{
private:
    bool firstMoveFlag;
    float moveSpeed = 5.0f, turnSpeed = 0.1f, deltaTime = 0.0f, lastFrame = 0.0f, viewRange = 100.0f;
    glm::mat4 view, projection;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 worldUp, camFront, camRight;
    glm::vec2 viewTarget, curViewTarget;
    float yaw, pitch;

    Camera();
    void updateValues();

public:
    void initiate();
    void checkKeys();
    void mouseMove(float x, float y);
    void updateScreenSize();
    glm::mat4 getViewProjection();

    static Camera &GET();
};