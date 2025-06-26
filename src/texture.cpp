#include "texture.hpp"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *imagePath) {
  int width, height, nChannels; 
  // Load Texture Data
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(imagePath, &width, &height, &nChannels, 0);

  if (!data) {
    std::cerr << "Could not load texture data\n";
    exit(EXIT_FAILURE);
  }

  // Parse Image Format
  size_t len = strlen(imagePath);
  std::string extension = { imagePath[len - 3], imagePath[len - 2], imagePath[len - 1] };
  GLenum format;

  if (extension == "jpg")
    format = GL_RGB;
  else if (extension == "png")
    format = GL_RGBA;

  // Create OpenGL Texture
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Clean-Up
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);
}
