#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

// Forward declarations
class VulkanDevice;
class Window;

class VulkanSwapChain {
public:
    VulkanSwapChain(VulkanDevice& device, Window& window);
    // Overloaded constructor for recreating the swapchain (e.g., on resize)
    VulkanSwapChain(VulkanDevice& device, Window& window, std::shared_ptr<VulkanSwapChain> previous);
    ~VulkanSwapChain();

    // No copying or moving
    VulkanSwapChain(const VulkanSwapChain&) = delete;
    VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
    VulkanSwapChain(VulkanSwapChain&&) = delete;
    VulkanSwapChain& operator=(VulkanSwapChain&&) = delete;

    // --- Public Getters ---
    VkSwapchainKHR getSwapChain() const { return swapChain; }
    VkRenderPass getRenderPass() const { return renderPass; }
    VkFramebuffer getFrameBuffer(int index) const { return swapChainFramebuffers[index]; }
    VkExtent2D getSwapChainExtent() const { return swapChainExtent; }
    uint32_t getImageCount() const { return static_cast<uint32_t>(swapChainImages.size()); }

    // --- Public Functions ---
    VkResult acquireNextImage(uint32_t* imageIndex, VkSemaphore imageAvailableSemaphore);
    VkResult submitCommandBuffers(const VkCommandBuffer* buffers, const uint32_t* imageIndex, VkSemaphore renderFinishedSemaphore);


private:
    void init();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();

    // Helper functions
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    // --- Member Variables ---
    VulkanDevice& vulkanDevice;
    Window& window;

    VkSwapchainKHR swapChain = VK_NULL_HANDLE;
    std::shared_ptr<VulkanSwapChain> oldSwapChain; // Used for recreation

    // Swap Chain Components
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkRenderPass renderPass;
};
