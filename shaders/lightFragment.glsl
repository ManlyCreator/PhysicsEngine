#version 330 core

uniform vec3 fragCol;

out vec4 col;

void main(void) {
  col = vec4(fragCol, 1.0f);
}
