#include "CameraController.h"
#include "../core/Window.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm> // For std::clamp

// --- Control constants ---
constexpr float MOUSE_SENSITIVITY = 0.005f;
constexpr float PAN_SPEED = 0.005f;
constexpr float ZOOM_SPEED = 0.5f;
constexpr float KEY_PAN_SPEED = 1.5f;

// --- Static pointer for the scroll callback ---
// GLFW callbacks are C functions, so they can't call member functions directly.
// This static pointer lets the C callback function find the C++ object instance.
static CameraController* s_instance = nullptr;

static void scrollCallback(GLFWwindow* window
    , double xoffset, double yoffset) {
    if (s_instance) {
        s_instance->processMouseScroll(yoffset);
    }
}

CameraController::CameraController(Camera& cam) : camera(cam) {
    s_instance = this;
}

void CameraController::connectWindow(Window& win) {
    glfwWindow = win.getGlfwWindow();
    glfwSetScrollCallback(glfwWindow, scrollCallback);
    glfwGetCursorPos(glfwWindow, &lastMouseX, &lastMouseY);
}

void CameraController::update(float dt) {
    if (!glfwWindow) return;

    processKeyboardInput(dt);
    processMouseInput();

    // Calculate final camera position from orbital parameters
    glm::vec3 direction;
    direction.x = cos(pitch) * sin(yaw);
    direction.y = sin(pitch);
    direction.z = cos(pitch) * cos(yaw);
    
    glm::vec3 position = focalPoint - glm::normalize(direction) * distance;
    
    camera.setViewTarget(position, focalPoint, glm::vec3{0.f, -1.f, 0.f});
}

void CameraController::processKeyboardInput(float dt) {
    glm::vec3 moveDir{0.f};
    if (glfwGetKey(glfwWindow, GLFW_KEY_UP) == GLFW_PRESS) moveDir.y += 1.f;
    if (glfwGetKey(glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS) moveDir.y -= 1.f;
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS) moveDir.x -= 1.f;
    if (glfwGetKey(glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) moveDir.x += 1.f;

    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
        // Get camera's current orientation to pan correctly
        glm::vec3 forward = glm::normalize(focalPoint - camera.getPosition());
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3{0.f, -1.f, 0.f}));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));
        
        focalPoint += (right * moveDir.x + up * moveDir.y) * KEY_PAN_SPEED * dt;
    }
}

void CameraController::processMouseInput() {
    double currentMouseX, currentMouseY;
    glfwGetCursorPos(glfwWindow, &currentMouseX, &currentMouseY);
    
    const float deltaX = static_cast<float>(currentMouseX - lastMouseX);
    const float deltaY = static_cast<float>(currentMouseY - lastMouseY);
    
    lastMouseX = currentMouseX;
    lastMouseY = currentMouseY;
    
    // Check if the middle mouse button is pressed
    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        const bool isShiftPressed = glfwGetKey(glfwWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(glfwWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;

        if (isShiftPressed) {
            // Pan (Shift + MMB)
            glm::vec3 forward = glm::normalize(focalPoint - camera.getPosition());
            glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3{0.f, -1.f, 0.f}));
            glm::vec3 up = glm::normalize(glm::cross(right, forward));

            // Scale pan speed by distance to feel more natural
            focalPoint -= right * deltaX * PAN_SPEED * distance;
            focalPoint += up * deltaY * PAN_SPEED * distance;
        } else {
            // Orbit (MMB)
            yaw -= deltaX * MOUSE_SENSITIVITY;
            pitch -= deltaY * MOUSE_SENSITIVITY;
            // Clamp pitch to avoid flipping upside down
            pitch = std::clamp(pitch, -glm::half_pi<float>() + 0.1f, glm::half_pi<float>() - 0.1f);
        }
    }
}

void CameraController::processMouseScroll(double yoffset) {
    distance -= static_cast<float>(yoffset) * ZOOM_SPEED;
    distance = std::clamp(distance, 2.0f, 50.0f);
}