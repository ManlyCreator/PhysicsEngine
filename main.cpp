#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <AnalogPhysics/sphere.hpp>
#include <AnalogPhysics/particle.hpp>
#include <shader.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 15.0f

// TODO: Calculate the total size of sphere vectors & account for it in the drawing logic
// TODO: Create a scene with lighted spheres
// TODO: Game Physics - Pg. 78
// TODO: Consult cyclone source code to organize this project

int main(void) {
  double timeElapsed = 0.0f;
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
  Shader sphereShader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

  // Particle
  AnalogPhysics::Sphere s(16, 16, 1.0, sphereShader);
  /*AnalogPhysics::Particle particle(shader, 0.0f);*/
  /*particle.size = glm::vec3(1.0f);*/
  /*particle.gravity = glm::vec3(0.0f, -GRAVITY, 0.0f);*/
  /*particle.damping = 0.995f;*/
  /*particle.SetMass(10.0f);*/

  // Projection
  /*glm::mat4 projection = glm::ortho((float)-WIDTH, (float)WIDTH, (float)-HEIGHT, (float)HEIGHT, -1.0f, 1.0f);*/
  glm::mat4 projection = glm::perspective((float)M_PI/2.0f, (float)WIDTH/HEIGHT, 0.1f, 100.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /*shader.SetMatrix4("projection", projection);*/
    /*shader.SetMatrix4("view", view);*/
    sphereShader.SetMatrix4("projection", projection);
    sphereShader.SetMatrix4("view", view);

    /*particle.Integrate(glfwGetTime() - timeElapsed);*/
    /*particle.Draw();*/
    s.Draw();

    timeElapsed = glfwGetTime();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}
