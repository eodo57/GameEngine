cmake_minimum_required(VERSION 3.20)
project(MyGameEngine)

set(CMAKE_CXX_STANDARD 20)

# Find packages
find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(glm REQUIRED)
find_package(tinyobjloader REQUIRED) # <-- NEW: Find the tinyobjloader library

pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)

# Automatically find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(engine ${SOURCES})

# Link libraries
target_link_libraries(engine
    Vulkan::Vulkan
    PkgConfig::GLFW
    tinyobjloader::tinyobjloader # <-- NEW: Link the tinyobjloader library
    dl pthread
)
target_link_libraries(engine glm::glm)

# Includes
target_include_directories(engine PRIVATE ${Vulkan_INCLUDE_DIRS})
# No need to add src/core, GLOB_RECURSE handles it

# Debug validation layers
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(engine PRIVATE VK_LAYER_LUNARG_standard_validation=1)
endif()