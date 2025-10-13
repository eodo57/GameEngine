#pragma once

#include "VulkanDevice.h"

// Use GLM for vector types
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal; // <-- NEW
        glm::vec2 uv;     // <-- NEW

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };

    Mesh(VulkanDevice& device, const std::vector<Vertex>& vertices);
    ~Mesh();

    // No copying or moving
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

private:
    void createVertexBuffer(const std::vector<Vertex>& vertices);

    VulkanDevice& vulkanDevice;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
};
