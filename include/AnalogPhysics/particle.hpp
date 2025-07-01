#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <glm/common.hpp>
#include <shader.hpp>
#include <ostream>
#include <shape.hpp>

typedef float real;

namespace AnalogPhysics {
  class Particle {
    private:
      real inverseMass;
      Shape shape;

    public:
      glm::vec3 position, velocity, acceleration, accumForce, gravity, size;
      real damping;

      Particle(Shape shape, real mass = 1.0f);
      void Integrate(real delta);
      void Render();
      inline void SetMass(real newMass) { inverseMass = 1.0f/newMass; }
      inline real GetInverseMass() { return inverseMass; }

      friend std::ostream &operator<<(std::ostream &out, glm::vec3 &v); 
  };

  inline std::ostream &operator<<(std::ostream &out, glm::vec3 &v) {
    return out << "< " << v.x << ", " << v.y << ", " << v.z << " >";
  }
}

#endif
