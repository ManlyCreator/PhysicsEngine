#ifndef LINE_H
#define LINE_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "shader.hpp"

class Line {
  private:
    float width;
    GLuint VBO, VAO;
    Shader shader;

  public:
    glm::vec2 startPos, endPos;
    Line(Shader shader, float width = 1.0f);
    void Draw(glm::vec3 col);
};

#endif
