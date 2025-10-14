#version 450

// Input vertex data from your model file
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUv;

// Output to fragment shader
layout(location = 0) out vec3 fragColor;

// Uniform Buffer Object (UBO) for matrices from the CPU
layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

void main() {
    // Calculate the final vertex position in screen space
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    
    // Pass the vertex color to the fragment shader
    fragColor = inColor;
}
