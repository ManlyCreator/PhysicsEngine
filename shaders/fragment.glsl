#version 330 core

uniform vec3 fragCol;
uniform vec3 lightCol;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 fragNorm;

out vec4 col;

void main(void) {
  vec3 norm = normalize(fragNorm);

  // Ambient
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightCol;

  // Diffuse
  vec3 lightDir = normalize(lightPos - fragPos); 
  float diffuse = max(dot(lightDir, norm), 0.0f);

  // Specular
  float specularStrength = 0.5f;
  int shininess = 16;
  vec3 reflectDir = reflect(-lightDir, norm);
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0f), shininess) * specularStrength * lightCol;

  // Output
  vec3 result = (ambient + diffuse + specular) * fragCol;
  col = vec4(result, 1.0f);
}
