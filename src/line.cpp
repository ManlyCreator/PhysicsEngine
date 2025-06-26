#include "line.hpp"

Line::Line(Shader shader, float width) {
  float vertices[] = {
    // Coordinates
     0.0f, 0.0f,
     1.0f, 0.0f
  };

  this->shader = shader;
  this->width = width;
  startPos = glm::vec2(0.0f, 0.0f);
  endPos = glm::vec2(1.0f, 0.0f);

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);  
  glEnableVertexAttribArray(0);
}

void Line::Draw(glm::vec3 col) {
  float vertices[] = {
    startPos.x, startPos.y,
    endPos.x, endPos.y
  };

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  shader.Use();
  shader.SetVector3("fragCol", col);

  glLineWidth(width);
  glDrawArrays(GL_LINES, 0, 2);
}
