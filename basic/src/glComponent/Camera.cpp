#include "Camera.h"

void Camera::keyUpdate()
{
    bool *keys = ScreenState::KeyState();
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float velocity = deltaTime * moveSpeed;

    if (keys[GLFW_KEY_W])
        pos += camFront * velocity;
    if (keys[GLFW_KEY_S])
        pos -= camFront * velocity;
    if (keys[GLFW_KEY_A])
        pos -= camRight * velocity;
    if (keys[GLFW_KEY_D])
        pos += camRight * velocity;
    if (keys[GLFW_KEY_SPACE])
        pos += worldUp * velocity;
    if (keys[GLFW_KEY_LEFT_SHIFT])
        pos -= worldUp * velocity;
    updateViewProjection();
}

void Camera::mouseUpdate(float x, float y)
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
    if (pitch > 90.0f)
        pitch = 90.0f;
    if (pitch < -90.0f)
        pitch = -90.0f;

    updateCameraNormals();
}

void Camera::updateCameraNormals()
{
    camFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront.y = sin(glm::radians(pitch));
    camFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(camFront);

    camRight = glm::normalize(glm::cross(camFront, worldUp));
    camUp = glm::cross(camRight, camFront);
    updateViewProjection();
}

void Camera::screenUpdate()
{
    float width = ScreenState::Width();
    float height = ScreenState::Height();
    projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, viewRange);
    updateViewProjection();
}

void Camera::updateViewProjection()
{
    view = glm::lookAt(pos, pos + camFront, camUp);
    viewProjection = projection * view;
}