#include <AnalogShapes/sphere.hpp>
#include <cmath>

namespace AnalogShapes {
  Sphere::Sphere(int sectors, int stacks, float radius) {
    buildVertices(sectors, stacks, radius);
    // TODO: OpenGL Logic
  }

  void Sphere::buildVertices(int sectors, int stacks, float radius) {
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
