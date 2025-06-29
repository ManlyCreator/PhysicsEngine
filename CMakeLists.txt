cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

project(PhysicsEngine)

add_compile_definitions(NAME="${PROJECT_NAME}")

add_executable(${PROJECT_NAME} main.cpp)

include_directories(include/)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glfw glm)

add_library(Shader STATIC src/shader.cpp)
add_library(Sphere STATIC src/AnalogPhysics/sphere.cpp)
add_library(Particle STATIC src/AnalogPhysics/particle.cpp)
add_library(Line STATIC src/line.cpp)
add_library(glad STATIC src/glad.c)

target_link_libraries(${PROJECT_NAME} glad glfw glm Shader Sphere Particle Line)
