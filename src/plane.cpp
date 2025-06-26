#include "plane.hpp"
#include "texture.hpp"

Plane::Plane() {
  GLuint VBO;

  float vertices[] = {
    // Coordinates // Colors         // Texture
    -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

     0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  };

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 2));  
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 5));  
  glEnableVertexAttribArray(2);
}

void Plane::Draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
