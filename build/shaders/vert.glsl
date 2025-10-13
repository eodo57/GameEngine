#version 450

layout(location = 0) out vec3 fragColor;

// Hardcode the positions of our triangle's vertices
vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
                           vec2(0.5, 0.5),
                           vec2(-0.5, 0.5)
);

// Hardcode the colors for each vertex
vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0), // Red
                        vec3(0.0, 1.0, 0.0), // Green
                        vec3(0.0, 0.0, 1.0)  // Blue
);

void main() {
    // gl_VertexIndex is a built-in variable that gives us the index of the current vertex (0, 1, or 2)
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = colors[gl_VertexIndex];
}
