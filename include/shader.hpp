#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
  private:
    GLuint ID;
    bool CheckCompileStatus(GLuint shader, GLenum shaderType);
    bool CheckLinkStatus();

  public:
    Shader() { };
    Shader(const char *vertexShader, const char *fragmentShader);
    void Use() { glUseProgram(ID); };
    GLuint GetID() { return ID; };
    void SetInt(const char *name, int value) { glUniform1i(glGetUniformLocation(ID, name), value); };
    void SetBool(const char *name, int value) { glUniform1i(glGetUniformLocation(ID, name), value); };
    void SetFloat(const char *name, float value) { glUniform1f(glGetUniformLocation(ID, name), value); };
    void SetVector3(const char *name, glm::vec3 value) { 
      glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value)); 
    };
    void SetMatrix4(const char *name, glm::mat4 value) { 
      glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value)); 
    };
    void SetLight(glm::vec3 pos, glm::vec3 col) {
      Use();
      SetVector3("lightPos", pos);
      SetVector3("lightCol", col);
    }
};

#endif
