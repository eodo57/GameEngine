#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

void Camera::setOrthographicProjection(float left, float right, float top, float bottom, float near, float far) {
    projectionMatrix = glm::mat4{1.0f};
    projectionMatrix[0][0] = 2.f / (right - left);
    projectionMatrix[1][1] = 2.f / (bottom - top);
    projectionMatrix[2][2] = 1.f / (far - near);
    projectionMatrix[3][0] = -(right + left) / (right - left);
    projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
    projectionMatrix[3][2] = -near / (far - near);
}

void Camera::setPerspectiveProjection(float fovy, float aspect, float near, float far) {
    if (aspect == 0.f) {
        throw std::invalid_argument("Aspect ratio cannot be zero.");
    }
    projectionMatrix = glm::perspective(fovy, aspect, near, far);
    // GLM is designed for OpenGL, which uses a different NDC y-coordinate direction.
    // Vulkan has Y pointing down, OpenGL has Y pointing up. We flip the y-axis.
    projectionMatrix[1][1] *= -1;
}

void Camera::setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up) {
    // Note: glm::lookAt requires a target point, not a direction.
    // So we calculate the target point by adding the direction to the position.
    const glm::vec3 target = position + direction;
    setViewTarget(position, target, up);
}

void Camera::setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    viewMatrix = glm::lookAt(position, target, up);
}

void Camera::setViewYXZ(glm::vec3 position, glm::vec3 rotation) {
    // This creates a view matrix based on Euler angles (Yaw, Pitch, Roll)
    // which is common for FPS-style cameras.
    const float c3 = glm::cos(rotation.z); // Roll
    const float s3 = glm::sin(rotation.z);
    const float c2 = glm::cos(rotation.x); // Pitch
    const float s2 = glm::sin(rotation.x);
    const float c1 = glm::cos(rotation.y); // Yaw
    const float s1 = glm::sin(rotation.y);
    
    viewMatrix = glm::mat4{
        {(c1 * c3 + s1 * s2 * s3), (c2 * s3), (c1 * s2 * s3 - s1 * c3), 0.0f},
        {(c3 * s1 * s2 - c1 * s3), (c2 * c3), (c1 * c2 * s3 + s1 * s2), 0.0f},
        {(c2 * s1), (-s2), (c1 * c2), 0.0f},
        {-position.x, -position.y, -position.z, 1.0f}};
}
