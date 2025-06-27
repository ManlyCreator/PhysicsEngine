#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <glm/common.hpp>
#include <shader.hpp>
#include <ostream>

typedef float real;

namespace AnalogPhysics {
  class Particle {
    private:
      GLuint VAO;
      real inverseMass;

    public:
      Shader shader;
      glm::vec3 position, velocity, acceleration, accumForce, gravity, size;
      real damping;

      Particle(Shader shader, real mass = 1.0f);
      void Draw();
      void Integrate(real delta);
      inline void SetMass(real newMass) { inverseMass = 1.0f/newMass; }
      inline real GetInverseMass() { return inverseMass; }

      friend std::ostream &operator<<(std::ostream &out, glm::vec3 &v); 
  };

  inline std::ostream &operator<<(std::ostream &out, glm::vec3 &v) {
    return out << "< " << v.x << ", " << v.y << ", " << v.z << " >";
  }
}

#endif
