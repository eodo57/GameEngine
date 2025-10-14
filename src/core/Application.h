#pragma once
#include "CameraController.h"
#include "../scene/GameObject.h"
#include <memory>

class Window;
class VulkanRenderer;

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void loadGameObjects();
    void castRayAndSelect(double mouseX, double mouseY);
    bool intersects(const Ray& ray, const GameObject& object);
    std::unique_ptr<Window> window;
    std::unique_ptr<VulkanRenderer> vulkanRenderer;
    std::vector<GameObject> gameObjects;
    std::unique_ptr<CameraController> cameraController;

    GameObject* selectedObject = nullptr;

    float lastFrameTime = 0.f;
};