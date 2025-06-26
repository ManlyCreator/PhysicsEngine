#include "shader.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char *vsPath, const char *fsPath) {
  GLuint vertexShader, fragmentShader;
  std::ifstream vsFile, fsFile;
  std::stringstream vsStream, fsStream;
  std::string vsSource, fsSource;

  // Vertex Shader
  vsFile.open(vsPath);
  vsStream << vsFile.rdbuf();
  vsSource = vsStream.str();
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, (const char**)&vsSource, NULL);
  glCompileShader(vertexShader);
  if (!CheckCompileStatus(vertexShader, GL_VERTEX_SHADER))
    std::exit(EXIT_FAILURE);

  // Fragment Shader
  fsFile.open(fsPath);
  fsStream << fsFile.rdbuf();
  fsSource = fsStream.str();
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, (const char**)&fsSource, NULL);
  glCompileShader(fragmentShader);
  if (!CheckCompileStatus(fragmentShader, GL_FRAGMENT_SHADER))
    std::exit(EXIT_FAILURE);

  // Program Linking
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  CheckLinkStatus();

  // Clean-Up
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

bool Shader::CheckCompileStatus(GLuint shader, GLenum shaderType) {
  int success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    switch (shaderType) {
      case GL_VERTEX_SHADER:
        std::cout << "VERTEX SHADER COMPILATION ERROR";
        break;
      case GL_FRAGMENT_SHADER:
        std::cout << "FRAGMENT SHADER COMPILATION ERROR";
        break;
    }
    std::cout << "\n" << infoLog;
    return false;
  }
  return true;
}

bool Shader::CheckLinkStatus() {
  int success;
  char infoLog[512];

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "PROGRAM LINKING ERROR\n" << infoLog;
    return false;
  }
  return true;
}
