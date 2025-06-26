#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <AnalogPhysics/particle.hpp>
#include <shader.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 800
#define HEIGHT 600

int main(void) {
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WIDTH, HEIGHT, NAME, nullptr, nullptr);

  if (!window) {
    std::cout << "Window creation failed\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to load OpenGL\n";
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  // Shader
  Shader shader("../shaders/vertex.glsl", "../shaders/circleFragment.glsl");

  // Particle
  AnalogPhysics::Particle particle(shader, 0.0f);
  particle.size = glm::vec3(100.0f);
  std::cout << particle.getInverseMass() << "\n";

  // Projection
  glm::mat4 projection = glm::ortho((float)-WIDTH, (float)WIDTH, (float)-HEIGHT, (float)HEIGHT, -1.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.SetMatrix4("projection", projection);

    particle.Draw();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}
