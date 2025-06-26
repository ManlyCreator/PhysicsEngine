#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
  private:
    GLuint ID;

  public:
    Texture(const char *imagePath);
    void Use() { glBindTexture(GL_TEXTURE_2D, ID); };
};


#endif
