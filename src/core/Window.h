#pragma once

#include <string>
#include <vulkan/vulkan.h>

// Forward declare GLFWwindow to avoid including the full GLFW header here
struct GLFWwindow;

class Window {
public:
    Window(int w, int h, const std::string& t);
    ~Window();

    // Not copyable or movable
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose();
    VkExtent2D getExtent() const { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
    
    // --- (FIX) Public getter for the GLFW window handle ---
    GLFWwindow* getGlfwWindow() const { return glfwWindow; }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

private:
    void initWindow();

    int width;
    int height;
    std::string title;

    GLFWwindow* glfwWindow;
};

