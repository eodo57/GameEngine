#pragma once

#include "../renderer/Camera.h"
#include "Window.h"
#include <glm/glm.hpp>

// Forward declare GLFWwindow
struct GLFWwindow;

class CameraController {
public:
    CameraController(Camera& cam);

    void connectWindow(Window& win);
    void update(float dt);

    // This needs to be public to be accessible by the static C-style callback
    void processMouseScroll(double yoffset);

private:
    void processKeyboardInput(float dt);
    void processMouseInput();

    Camera& camera;
    GLFWwindow* glfwWindow = nullptr;
    
    // Camera orbital state
    glm::vec3 focalPoint{0.f, 0.f, 2.5f}; // Start by looking at the default vase position
    float distance = 5.f;
    float yaw = 0.f;
    float pitch = glm::radians(-20.f);

    // Mouse state
    double lastMouseX = 0.0, lastMouseY = 0.0;
};
// In CameraController.h
glm::vec3 getMouseRay() {
    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(glfwWindow, &xpos, &ypos);

    // Convert to normalized device coordinates
    float x = (2.0f * xpos) / windowWidth - 1.0f;
    float y = 1.0f - (2.0f * ypos) / windowHeight;

    // Convert to 3D world space
    glm::mat4 invProj = glm::inverse(camera.getProjection());
    glm::mat4 invView = glm::inverse(camera.getView());
    glm::vec4 rayClip = glm::vec4(x, y, -1.0, 1.0);
    glm::vec4 rayEye = invProj * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);
    glm::vec3 rayWorld = glm::vec3(invView * rayEye);

    return glm::normalize(rayWorld);
}