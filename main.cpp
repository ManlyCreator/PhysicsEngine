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
#define GRAVITY 1.0f

// TODO: Camera Class
// TODO: Game Physics - Pg. 78
// TODO: Consolidate demos into separate source files that can be loaded through function calls

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
  Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
  Shader lightShader("../shaders/vertex.glsl", "../shaders/lightFragment.glsl");

  // Particle
  AnalogPhysics::Sphere lightSphere(16, 16, 1.0f, lightShader);
  AnalogPhysics::Sphere sphere(16, 16, 1.0f, shader);

  lightSphere.color = glm::vec3(1.0f);
  lightSphere.position = glm::vec3(-5.0f, 5.0f, 5.0f);

  sphere.color = glm::vec3(1.0f, 0.5f, 0.31f);

  shader.SetLight(lightSphere.position, lightSphere.color);

  AnalogPhysics::Particle particle(sphere, 0.0f);
  particle.size = glm::vec3(1.0f);
  particle.gravity = glm::vec3(0.0f, -GRAVITY, 0.0f);
  particle.damping = 0.995f;
  particle.SetMass(10.0f);

  // Shader Matrices
  glm::mat4 projection = glm::perspective((float)M_PI/4.0f, (float)WIDTH/HEIGHT, 0.1f, 100.0f);
  glm::vec3 cameraPos(0.0f, 0.0f, 20.0f);
  glm::mat4 view = glm::lookAt(cameraPos, particle.position, glm::vec3(0.0f, 1.0f, 0.0f));

  while (!glfwWindowShouldClose(window)) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Use();
    shader.SetMatrix4("projection", projection);
    view = glm::lookAt(cameraPos, particle.position, glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetMatrix4("view", view);
    shader.SetVector3("viewPos", cameraPos);
    lightShader.Use();
    lightShader.SetMatrix4("projection", projection);
    lightShader.SetMatrix4("view", view);

    lightSphere.Draw();
    particle.Integrate(glfwGetTime() - timeElapsed);
    particle.Render();

    timeElapsed = glfwGetTime();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();

  return 0;
}
