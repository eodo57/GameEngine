#pragma once

#include "VulkanDevice.h"
#include "Camera.h" // <-- Include camera
#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

struct UniformBufferObject {
    alignas(16) glm::vec4 color  ; // For object color
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    
};

class Window;
class GameObject; // <-- Forward-declare GameObject

class VulkanRenderer {
public:
    explicit VulkanRenderer(Window& window);
    ~VulkanRenderer();

    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer& operator=(const VulkanRenderer&) = delete;

    VulkanDevice& getDevice() const { return *vulkanDevice; }
    
    Camera& getCamera() { return camera; }

    void drawFrame(GameObject& gameObject); // <-- Updated signature
    void waitIdle() const;

private:
    void initVulkan();
    void cleanup();
    void cleanupSwapChain();
    
    // UBO and Descriptor Set functions
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createGrid();
    void createGridPipeline();
    void updateUniformBuffer(uint32_t currentImage, GameObject& gameObject);
    void createGridDescriptorPool();
    void createGridDescriptorSets();
    VkDescriptorPool gridDescriptorPool;
    std::vector<VkDescriptorSet> gridDescriptorSets;
    // Existing helper functions
private:
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void createGraphicsPipeline();

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkPipeline gridPipeline;
    VkPipelineLayout gridPipelineLayout;
    VkBuffer gridVertexBuffer;
    VkDeviceMemory gridVertexBufferMemory;

    uint32_t gridVertexCount;
    
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);

    Window& window;
    std::unique_ptr<VulkanDevice> vulkanDevice;
    
    // --- NEW UBO and Descriptor members ---
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    Camera camera{}; // <-- Add a camera object
    
    // Existing members
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    uint32_t currentFrame = 0;

    const int MAX_FRAMES_IN_FLIGHT = 2;
};