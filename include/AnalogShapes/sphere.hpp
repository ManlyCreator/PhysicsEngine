#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include <vector>

namespace AnalogShapes {
  class Sphere {
    private:
      GLuint VAO;
      std::vector<float> interleavedVertices, indices;

      void buildVertices(int sectors, int stacks, float radius);

    public:
      Sphere(int sectors, int stacks, float radius);
  };
}

#endif
