#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include <vector>
#include "shader.hpp"

namespace AnalogPhysics {
  class Shape {
    protected:
      unsigned VAO, EBO;
      std::vector<float> interleavedVertices;
      std::vector<unsigned> indices;
      Shader shader;
    public:
      void Draw(glm::mat4 model) {
        shader.Use(); 
        shader.SetMatrix4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
      }
  };
}

#endif
