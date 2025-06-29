#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout (location=0) in vec3 vertPos;
layout (location=1) in vec3 vertNorm;
layout (location=2) in vec2 vertTex;

void main(void) {
  gl_Position = projection * view * model * vec4(vertPos, 1.0f);
}
