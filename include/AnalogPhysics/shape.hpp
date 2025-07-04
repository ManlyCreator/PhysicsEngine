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
      glm::vec3 position;
      glm::vec3 color;

      virtual void Draw() {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        shader.Use(); 
        shader.SetMatrix4("model", model);
        shader.SetVector3("fragCol", color);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
      }

      virtual void SetLight(glm::vec3 lightPos, glm::vec3 lightCol) {
        shader.Use();
        shader.SetVector3("lightPos", lightPos);
        shader.SetVector3("lightCol", lightCol);
      }
  };
}

#endif
