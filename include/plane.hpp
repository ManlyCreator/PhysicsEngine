#ifndef PLANE_H
#define PLANE_H

#include <glad/glad.h>

class Plane {
  private:
    GLuint VAO;

  public:
    Plane();
    void Draw();
};

#endif
