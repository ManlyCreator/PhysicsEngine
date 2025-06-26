#include <AnalogPhysics/particle.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace AnalogPhysics {
  Particle::Particle(Shader shader, real mass) {
    this->shader = shader;
    inverseMass = 1.0f/mass;
    position = glm::vec3(0.0f);
    velocity = glm::vec3(0.0f);
    acceleration = glm::vec3(0.0f);
    size = glm::vec3(1.0f);

    unsigned VBO;
    float vertices[] = {
       1.0f,  1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,

       1.0f,  1.0f, 0.0f,
      -1.0f,  1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  }

  void Particle::Draw() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    shader.Use();
    shader.SetMatrix4("model", model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
}
