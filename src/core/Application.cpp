// In src/core/Application.cpp
#include "Application.h"
#include "Window.h"
#include "../renderer/VulkanRenderer.h"
#include "Logger.h"
#include <GLFW/glfw3.h>

Application::Application() {
    window = std::make_unique<Window>(WIDTH, HEIGHT, "Vulkan Engine");
    vulkanRenderer = std::make_unique<VulkanRenderer>(*window);

    // --- NEW: Load a model ---
    model = std::make_unique<Model>(*vulkanRenderer->getDevice(), "models/smooth_vase.obj");
}

// ... rest of the file is the same

Application::~Application() {
    // unique_ptr members will be automatically cleaned up, ensuring proper destruction order
}

void Application::run() {
    Logger::info("Application starting...");

    while (!window->shouldClose()) {
        glfwPollEvents();
        vulkanRenderer->drawFrame(*model);
    }

    // It's good practice to wait for the GPU to finish before exiting
    vulkanRenderer->waitIdle();

    Logger::info("Application shutting down.");
}

