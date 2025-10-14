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
    void processMouseScroll(double yoffset);

    // This is the function DECLARATION
    glm::vec3 getMouseRay();

private:
    void processKeyboardInput(float dt);
    void processMouseInput();

    Camera& camera;
    GLFWwindow* glfwWindow = nullptr;
    
    int windowWidth = 0;
    int windowHeight = 0;
    
    glm::vec3 focalPoint{0.f, 0.f, 2.5f};
    float distance = 5.f;
    float yaw = 0.f;
    float pitch = glm::radians(-20.f);

    double lastMouseX = 0.0, lastMouseY = 0.0;
};