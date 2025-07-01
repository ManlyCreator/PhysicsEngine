#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include <vector>
#include "shape.hpp"

namespace AnalogPhysics {
  class Sphere : public Shape {
    private:
      void BuildVertices(int sectors, int stacks, float radius);

    public:
      Sphere(int sectors, int stacks, float radius, Shader shader);
  };
}

#endif
