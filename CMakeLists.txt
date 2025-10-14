cmake_minimum_required(VERSION 4.1.2)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    engine $(SOURCE_DIRS src)
    src/main.cpp
    src/core/Application.cpp
    src/core/Window.cpp
    src/core/Logger.cpp
    src/core/CameraController.cpp # <-- ADD THIS LINE
    src/renderer/VulkanRenderer.cpp
    src/renderer/VulkanDevice.cpp
    src/renderer/VulkanSwapChain.cpp
    src/renderer/Pipeline.cpp
    src/renderer/Mesh.cpp
    src/renderer/Model.cpp
    src/renderer/Camera.cpp
    src/scene/GameObject.cpp)

find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Compile shaders
file(GLOB SHADERS "shaders/*.glsl")
foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)
    get_filename_component(SHADER_EXT ${SHADER} EXT)
    set(SPIRV_SHADER "${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}${SHADER_EXT}.spv")

    add_custom_command(
        OUTPUT ${SPIRV_SHADER}
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${SPIRV_SHADER}
        DEPENDS ${SHADER}
        COMMENT "Compiling GLSL shader: ${SHADER_NAME}${SHADER_EXT}")
    list(APPEND SPIRV_SHADERS ${SPIRV_SHADER})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SPIRV_SHADERS})
add_dependencies(engine Shaders)

target_include_directories(
    engine
    PRIVATE
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    vendor # For GLM and tiny_obj_loader
)

target_link_libraries(
    engine
    PRIVATE
    ${Vulkan_LIBRARIES}
    ${GLFW_LIBRARIES}
)

target_compile_definitions(engine PRIVATE GLFW_INCLUDE_VULKAN)