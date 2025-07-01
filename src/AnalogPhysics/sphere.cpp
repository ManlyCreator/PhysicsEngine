#include "AnalogPhysics/particle.hpp"
#include "line.hpp"
#include <AnalogPhysics/sphere.hpp>
#include <cmath>
#include <iostream>

namespace AnalogPhysics {
  Sphere::Sphere(int sectors, int stacks, float radius, Shader shader) {
    GLuint VBO;

    this->shader = shader;

    BuildVertices(sectors, stacks, radius);
    GLenum err;

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * sizeof(float), interleavedVertices.data(), GL_STATIC_DRAW);
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }
    glEnableVertexAttribArray(1);

    // Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void Sphere::Draw() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
    shader.Use(); 
    shader.SetMatrix4("model", model);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }
    glBindVertexArray(0);
  }

  void Sphere::BuildVertices(int sectors, int stacks, float radius) {
    float x, y, z, xz;
    float sectorAngle, stackAngle;
    float sectorStep = 2*M_PI / sectors;
    float stackStep = M_PI / stacks;

    for (int i = 0; i < stacks; i++) {
      stackAngle = M_PI/2 - i*stackStep; 
      xz = radius * cosf(stackAngle);
      y = radius * sinf(stackAngle);

      for (int j = 0; j < sectors; j++) {
        sectorAngle = j * sectorStep;

        x = xz * cosf(sectorAngle);
        z = xz * sinf(sectorAngle);

        // Vertices
        interleavedVertices.push_back(x);
        interleavedVertices.push_back(y);
        interleavedVertices.push_back(z);

        // Normals
        interleavedVertices.push_back(x / radius);
        interleavedVertices.push_back(y / radius);
        interleavedVertices.push_back(z / radius);

        // Texture
        interleavedVertices.push_back((float)j / sectors);
        interleavedVertices.push_back((float)i / stacks);
      }
    }

    unsigned k1, k2;

    for (int i = 0; i < stacks; i++) {
      k1 = i * (sectors + 1);
      k2 = k1 + sectors + 1;
      
      for (int j = 0; j < sectors; j++, k1++, k2++) {
        if (i != 0) {
          indices.push_back(k1);
          indices.push_back(k2);
          indices.push_back(k1 + 1);
        }

        if (i != stacks - 1) {
          indices.push_back(k1 + 1);
          indices.push_back(k2);
          indices.push_back(k2 + 1);
        }
      }
    }
  }
}
