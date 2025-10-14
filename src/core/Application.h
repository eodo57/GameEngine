#pragma once

#include "Window.h"
#include "../renderer/VulkanRenderer.h"
#include "../scene/GameObject.h"
#include "CameraController.h"
#include "../renderer/Ray.h" // <-- Make sure this is included


class Application {
public:
    Application();
    ~Application();

    void run();

private:
    void castRayAndSelect(double mouseX, double mouseY);
    bool intersects(const Ray& ray, const GameObject& object);

    Window window;
    VulkanRenderer renderer;
    GameObject gameObject;
    CameraController cameraController;
    GameObject* selectedObject = nullptr;
};