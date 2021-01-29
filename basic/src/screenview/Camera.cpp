#include "Camera.h"

Camera::Camera()
{
    firstMoveFlag = true;
    initiate();
}

void Camera::initiate()
{
    yaw = -90.0f;
    pitch = 0.0f;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::checkKeys()
{
    bool *keys = ScreenState::KeyState();
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float velocity = deltaTime * moveSpeed;

    if (keys[GLFW_KEY_W])
    {
        pos += camFront * velocity;
    }
    if (keys[GLFW_KEY_S])
    {
        pos -= camFront * velocity;
    }
    if (keys[GLFW_KEY_A])
    {
        pos -= camRight * velocity;
    }
    if (keys[GLFW_KEY_D])
    {
        pos += camRight * velocity;
    }
    if (keys[GLFW_KEY_SPACE])
    {
        pos += worldUp * velocity;
    }
    if (keys[GLFW_KEY_LEFT_SHIFT])
    {
        pos -= worldUp * velocity;
    }
    updateViewProjection();
}

void Camera::mouseMove(float x, float y)
{
    if (firstMoveFlag)
    {
        curViewTarget = {x * turnSpeed, y * turnSpeed};
        firstMoveFlag = false;
    }
    viewTarget = curViewTarget;
    curViewTarget = {x * turnSpeed, y * turnSpeed};

    pitch += viewTarget.y - curViewTarget.y;
    yaw += curViewTarget.x - viewTarget.x;

    // constrains pitch
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateValues();
}

void Camera::updateValues()
{
    camFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront.y = sin(glm::radians(pitch));
    camFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(camFront);

    camRight = glm::normalize(glm::cross(camFront, worldUp));
    camUp = glm::cross(camRight, camFront);
    updateViewProjection();
}

void Camera::updateViewProjection()
{
    view = glm::lookAt(pos, pos + camFront, camUp);
    viewProjection = projection * view;
}

void Camera::updateScreenSize()
{
    float width = ScreenState::Width();
    float height = ScreenState::Height();
    projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, viewRange);
    updateViewProjection();
}