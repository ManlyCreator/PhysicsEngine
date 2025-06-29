#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include <vector>
#include <shader.hpp>

namespace AnalogPhysics {
  class Sphere {
    private:
      GLuint VAO, EBO;
      std::vector<float> interleavedVertices, indices;
      Shader shader;

      void BuildVertices(int sectors, int stacks, float radius);

    public:
      Sphere(int sectors, int stacks, float radius, Shader shader);
      void Draw();
  };
}

#endif
