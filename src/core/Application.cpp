#include "Application.h"
#include "Logger.h"

Application::Application() : window(800, 600, "Vulkan Game Engine"), renderer(window), cameraController(renderer.getCamera()) {
    Logger::info("Application starting...");
    gameObject.model = std::make_shared<Model>(renderer.getDevice(), "models/airboat.obj");
    gameObject.transform.translation = {0.0f, 0.0f, -2.5f};
}

Application::~Application() {
    Logger::info("Application shutting down...");
}

void Application::run() {
    while (!window.shouldClose()) {
        glfwPollEvents();

        int mouseState = glfwGetMouseButton(window.getGlfwWindow(), GLFW_MOUSE_BUTTON_LEFT);
        if (mouseState == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window.getGlfwWindow(), &xpos, &ypos);
            castRayAndSelect(xpos, ypos);
        }

        cameraController.update(0.016f);
        renderer.drawFrame(gameObject);
    }
    renderer.waitIdle();
}

void Application::castRayAndSelect(double mouseX, double mouseY) {
    int width, height;
    glfwGetWindowSize(window.getGlfwWindow(), &width, &height);
    Ray ray = renderer.getCamera().castRay(static_cast<float>(mouseX), static_cast<float>(mouseY), width, height);

    float closest_t = std::numeric_limits<float>::max();
    GameObject* hitObject = nullptr;

    if (intersects(ray, gameObject)) {
         hitObject = &gameObject;
    }

    if (selectedObject) {
        selectedObject->selected = false;
    }

    if (hitObject) {
        selectedObject = hitObject;
        selectedObject->selected = true;
        Logger::info("Object selected!");
    } else {
        selectedObject = nullptr;
        Logger::info("No object selected.");
    }
}

bool Application::intersects(const Ray& ray, const GameObject& object) {
    float radius = 1.0f;
    glm::vec3 oc = ray.origin - object.transform.translation;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}