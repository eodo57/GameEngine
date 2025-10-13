cmake_minimum_required(VERSION 3.20)
project(MyGameEngine)

set(CMAKE_CXX_STANDARD 20)

# Find packages
find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(glm REQUIRED)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)  # Arch-friendly GLFW detection

# Executable
add_executable(engine src/main.cpp)

# Link libraries
target_link_libraries(engine 
    Vulkan::Vulkan 
    PkgConfig::GLFW  # Links GLFW + its deps (X11, etc.)
    dl pthread
)
target_link_libraries(engine glm::glm)

# Includes
target_include_directories(engine PRIVATE ${Vulkan_INCLUDE_DIRS})
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/src/core)
# Debug validation layers
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(engine PRIVATE VK_LAYER_LUNARG_standard_validation=1)
endif()