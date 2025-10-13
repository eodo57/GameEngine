#include "Application.h"
#include "Window.h"
#include "../renderer/VulkanRenderer.h"
#include "../renderer/Model.h" // Correct path to Model.h
#include "Logger.h"
#include <GLFW/glfw3.h>
#include <memory>

Application::Application() {
    window = std::make_unique<Window>(WIDTH, HEIGHT, "Vulkan Engine");
    vulkanRenderer = std::make_unique<VulkanRenderer>(*window);

    // FIX: Removed the incorrect '*' dereference operator
    model = std::make_unique<Model>(vulkanRenderer->getDevice(), "models/smooth_vase.obj");
}

Application::~Application() {}

void Application::run() {
    Logger::info("Application starting...");

    while (!window->shouldClose()) {
        glfwPollEvents();
        vulkanRenderer->drawFrame(*model);
    }

    vulkanRenderer->waitIdle();
    Logger::info("Application shutting down.");
}