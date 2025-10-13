#pragma once

#include "../renderer/Model.h"
#include <memory>

// Forward declarations to avoid including full headers here
class Window;
class VulkanRenderer;

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    Application();
    ~Application();

    // Not copyable or movable
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    std::unique_ptr<Window> window;
    std::unique_ptr<VulkanRenderer> vulkanRenderer;
};

