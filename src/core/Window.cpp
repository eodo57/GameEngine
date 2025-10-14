// Define this macro BEFORE including glfw3.h to include Vulkan headers
//#define GLFW_INCLUDE_VULKAN // <-- FIX: Changed 'Vulkan' to 'VULKAN'
#include <GLFW/glfw3.h>

#include "Window.h"
#include <stdexcept>

// Constructor: Stores window properties and initializes the window.
Window::Window(int w, int h, const std::string& t) : width(w), height(h), title(t) {
    initWindow();
}

// Destructor: Cleans up GLFW resources.
Window::~Window() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

// Initializes the GLFW library and creates the window.
void Window::initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!glfwWindow) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }
}

// Creates the Vulkan surface.
void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
    if (glfwCreateWindowSurface(instance, glfwWindow, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }
}

