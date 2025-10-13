#include "Application.h"

// Include the full class definitions here in the .cpp file
#include "Window.h"
#include "../renderer/VulkanRenderer.h"
#include "Logger.h"

// GLFW is needed for polling events
#include <GLFW/glfw3.h>

Application::Application() {
    // Now the compiler knows the full definition of Window and VulkanRenderer
    window = std::make_unique<Window>(WIDTH, HEIGHT, "Vulkan Engine");
    vulkanRenderer = std::make_unique<VulkanRenderer>(*window);
}

Application::~Application() {
    // unique_ptr members will be automatically cleaned up, ensuring proper destruction order
}

void Application::run() {
    Logger::info("Application starting...");

    while (!window->shouldClose()) {
        glfwPollEvents();
        vulkanRenderer->drawFrame();
    }

    // It's good practice to wait for the GPU to finish before exiting
    vulkanRenderer->waitIdle();

    Logger::info("Application shutting down.");
}

