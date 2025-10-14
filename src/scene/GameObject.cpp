#include "TransformComponent.h" // <-- Change include from GameObject.h

// This implementation was in TransformComponent.h, move it here.
glm::mat4 TransformComponent::mat4() const {
    glm::mat4 transform = glm::translate(glm::mat4(1.f), translation);

    transform = glm::rotate(transform, rotation.y, {0.f, 1.f, 0.f}); // Yaw
    transform = glm::rotate(transform, rotation.x, {1.f, 0.f, 0.f}); // Pitch
    transform = glm::rotate(transform, rotation.z, {0.f, 0.f, 1.f}); // Roll

    transform = glm::scale(transform, scale);
    return transform;
}