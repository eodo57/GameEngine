#pragma once

#include <glm/gtc/matrix_transform.hpp>

struct TransformComponent {
    glm::vec3 translation{};  // Position offset
    glm::vec3 scale{1.f, 1.f, 1.f};
    glm::vec3 rotation{}; // Euler angles for rotation

    /**
     * @brief Computes the model matrix from the transform components.
     * * The matrix is calculated by first applying scale, then rotation, then translation.
     * The rotation order is Z, then X, then Y (Tait-Bryan angles), which is a common
     * convention for game engines.
     * * @return The 4x4 model matrix.
     */
    glm::mat4 mat4() const {
        // Start with identity matrix
        glm::mat4 transform = glm::mat4(1.0f);

        // 1. Translate
        transform = glm::translate(transform, translation);

        // 2. Rotate
        // Note: Rotations are applied in reverse order of multiplication.
        // To get a Z -> X -> Y rotation order, we multiply in Y -> X -> Z order.
        transform = glm::rotate(transform, rotation.y, {0.f, 1.f, 0.f}); // Yaw
        transform = glm::rotate(transform, rotation.x, {1.f, 0.f, 0.f}); // Pitch
        transform = glm::rotate(transform, rotation.z, {0.f, 0.f, 1.f}); // Roll

        // 3. Scale
        transform = glm::scale(transform, scale);
        
        return transform;
    }
};
