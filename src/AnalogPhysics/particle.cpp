#include <AnalogPhysics/particle.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace AnalogPhysics {
  Particle::Particle(Shape shape, real mass) {
    this->shape = shape;
    inverseMass = 1.0f/mass;
    position = glm::vec3(0.0f);
    velocity = glm::vec3(0.0f);
    acceleration = glm::vec3(0.0f);
    accumForce = glm::vec3(0.0f);
  }

  void Particle::Integrate(real delta) {
    // Calculate Acceleration
    acceleration = GetInverseMass() * accumForce + gravity;
    // Calculate Velocity
    velocity += acceleration * delta;
    // Impose Drag
    velocity *= powf(damping, delta); 
    // Update Position
    position += velocity * delta;
  }

  void Particle::Render() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    shape.Draw(model);
  }
}

