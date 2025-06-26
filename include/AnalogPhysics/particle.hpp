#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <glm/common.hpp>
#include <shader.hpp>

typedef float real;

namespace AnalogPhysics {
  class Particle {
    private:
      GLuint VAO;
      real inverseMass;

    public:
      Shader shader;
      glm::vec3 position, velocity, acceleration, size;
      real damping;

      Particle(Shader shader, real mass = 1.0f);
      void Draw();
      void setMass(real newMass) { inverseMass = 1.0f/newMass; }
      real getInverseMass() { return inverseMass; }
  };
}

#endif
