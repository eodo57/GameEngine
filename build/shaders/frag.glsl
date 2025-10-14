#version 450

// Input color interpolated from the vertex shader
layout(location = 0) in vec3 fragColor;

// Output color for the current pixel
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}
