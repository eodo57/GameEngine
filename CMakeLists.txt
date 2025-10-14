cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    engine
    src/main.cpp
    src/core/Application.cpp
    src/core/Window.cpp
    src/core/Logger.cpp
    src/core/CameraController.cpp
    src/renderer/VulkanRenderer.cpp
    src/renderer/VulkanDevice.cpp
    src/renderer/VulkanSwapChain.cpp
    src/renderer/Pipeline.cpp
    src/renderer/Mesh.cpp
    src/renderer/Model.cpp
    src/renderer/Camera.cpp
    src/scene/GameObject.cpp
)

find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Compile shaders
file(GLOB SHADERS "shaders/*.glsl")
foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)        # vert.glsl or frag.glsl
    get_filename_component(SHADER_TYPE ${SHADER_NAME} NAME_WE) # vert or frag
    set(SPIRV_SHADER "${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}.spv")

    add_custom_command(
        OUTPUT ${SPIRV_SHADER}
        # This command now includes the required shader stage flag
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} -fshader-stage=${SHADER_TYPE} ${SHADER} -o ${SPIRV_SHADER}
        DEPENDS ${SHADER}
        COMMENT "Compiling GLSL shader: ${SHADER_NAME}")
    list(APPEND SPIRV_SHADERS ${SPIRV_SHADER})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SPIRV_SHADERS})
add_dependencies(engine Shaders)

target_include_directories(
    engine
    PRIVATE
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    vendor
)

target_link_libraries(
    engine
    PRIVATE
    ${Vulkan_LIBRARIES}
    ${GLFW_LIBRARIES}
)

target_compile_definitions(engine PRIVATE GLFW_INCLUDE_VULKAN)