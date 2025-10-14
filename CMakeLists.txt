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
set(GLSL_SHADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vert.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/frag.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/grid.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/grid.frag
)

foreach(SHADER_PATH ${GLSL_SHADERS})
    get_filename_component(SHADER_NAME ${SHADER_PATH} NAME)

    # Determine the shader stage by checking if the filename contains "vert" or "frag"
    if("${SHADER_NAME}" MATCHES "vert")
        set(SHADER_STAGE "vert")
    elseif("${SHADER_NAME}" MATCHES "frag")
        set(SHADER_STAGE "frag")
    else()
        message(FATAL_ERROR "Unknown shader type for ${SHADER_NAME}. Name must contain 'vert' or 'frag'.")
    endif()

    set(SPIRV_SHADER "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER_NAME}.spv")

    add_custom_command(
        OUTPUT ${SPIRV_SHADER}
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} -fshader-stage=${SHADER_STAGE} ${SHADER_PATH} -o ${SPIRV_SHADER}
        DEPENDS ${SHADER_PATH}
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