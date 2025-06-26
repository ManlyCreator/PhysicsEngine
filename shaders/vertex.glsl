#version 330 core

uniform mat4 projection;
uniform mat4 model;

layout (location=0) in vec3 vertPos;

out vec2 fragPos;

void main(void) {
  gl_Position = projection * model * vec4(vertPos, 1.0f);
  fragPos = vec2(vertPos.x, vertPos.y);
}
