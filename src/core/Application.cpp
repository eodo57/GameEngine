#include "Application.h"
#include "Window.h"
#include "../renderer/VulkanRenderer.h"
#include "../renderer/Model.h"
#include "../scene/GameObject.h" 
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
        int mouseState = glfwGetMouseButton(window->getGlfwWindow(), GLFW_MOUSE_BUTTON_LEFT);
        if (mouseState == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window->getGlfwWindow(), &xpos, &ypos);
            castRayAndSelect(xpos, ypos);
        }
        // Update the camera
        cameraController->update(deltaTime);
        
        vulkanRenderer->drawFrame(gameObjects[0]);
    }

    vulkanRenderer->waitIdle();
    Logger::info("Application shutting down.");
}

void Application::castRayAndSelect(double mouseX, double mouseY) {
    int width, height;
    glfwGetWindowSize(window->getGlfwWindow(), &width, &height);
    Ray ray = renderer.getCamera().castRay(static_cast<float>(mouseX), static_cast<float>(mouseY), width, height);

    // Simple intersection test (replace with a more robust one later)
    float closest_t = std::numeric_limits<float>::max();
    GameObject* hitObject = nullptr;

    // This assumes you have a list of gameObjects to test against.
    // For now, we only have one `gameObject` in the Application class.
    // We'll expand this later.
    if (intersects(ray, gameObject)) {
         hitObject = &gameObject;
    }


    if (selectedObject) {
        selectedObject->selected = false; // Deselect the old object
    }

    if (hitObject) {
        selectedObject = hitObject;
        selectedObject->selected = true; // Select the new object
        Logger::info("Object selected!");
    } else {
        selectedObject = nullptr;
        Logger::info("No object selected.");
    }
}

bool Application::intersects(const Ray& ray, const GameObject& object) {
    // A simple sphere-ray intersection test
    // We'll assume a bounding sphere for the object for now
    float radius = 1.0f; // A placeholder radius
    glm::vec3 oc = ray.origin - object.transform.translation;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}