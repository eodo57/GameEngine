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