#include "Application.h"
#include "Window.h"
#include "../renderer/VulkanRenderer.h"
#include "../renderer/Model.h"
#include "../scene/GameObject.h" // <-- Make sure this is included
#include "Logger.h"
#include <GLFW/glfw3.h>

Application::Application() {
    window = std::make_unique<Window>(WIDTH, HEIGHT, "Vulkan Engine");
    vulkanRenderer = std::make_unique<VulkanRenderer>(*window);

    // Create and connect the camera controller
    cameraController = std::make_unique<CameraController>(vulkanRenderer->getCamera());
    cameraController->connectWindow(*window);

    loadGameObjects();
}

Application::~Application() {}

void Application::loadGameObjects() {
    std::shared_ptr<Model> model = std::make_shared<Model>(vulkanRenderer->getDevice(), "models/airboat.obj");

    auto vase = GameObject::createGameObject();
    vase.model = model; // This will now work
    vase.transform.translation = {0.f, 0.f, 2.5f};
    vase.transform.scale = {3.f, 3.f, 3.f};
    gameObjects.push_back(std::move(vase));
}

void Application::run() {
    Logger::info("Application starting...");

    while (!window->shouldClose()) {
        glfwPollEvents();

                // Calculate delta time
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // Update the camera
        cameraController->update(deltaTime);
        
        vulkanRenderer->drawFrame(gameObjects[0]);
    }

    vulkanRenderer->waitIdle();
    Logger::info("Application shutting down.");
}