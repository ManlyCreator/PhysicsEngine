#version 330 core

in vec2 fragPos;

out vec4 col;

void main(void) {
  float d = length(fragPos);
  float mask = smoothstep(0.99f, 0.98f, d);
  col = vec4(1.0f) * mask;
}
