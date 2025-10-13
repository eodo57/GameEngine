#pragma once

#include "VulkanDevice.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <memory>

class Model {
public:
    Model(VulkanDevice& device, const std::string& filepath);
    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

private:
    void createVertexBuffers(const std::vector<Mesh::Vertex>& vertices);
    void createIndexBuffers(const std::vector<uint32_t>& indices);

    VulkanDevice& vulkanDevice;
    std::unique_ptr<Mesh> mesh;

    bool hasIndexBuffer = false;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    uint32_t indexCount;
};