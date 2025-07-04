#include "camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(glm::vec3 pos) {
  this->pos = pos;
  yaw = -90.0f;
  pitch = 0.0f;
  front = glm::vec3(0.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
  UpdateView();
}

void Camera::UpdateView() {
  glm::vec3 dir;
  dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  dir.y = sin(glm::radians(pitch));
  dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(dir);
  view = glm::lookAt(pos, pos + front, up);
}

void Camera::ProcessCursor(float deltaX, float deltaY) {
  if (glm::abs(deltaX) > 100.0f || glm::abs(deltaY) > 100.0f) return;
  yaw += deltaX;
  pitch = glm::clamp(pitch - deltaY, -89.9f, 89.9f);
  UpdateView();
}

void Camera::ProcessKeyboard(float deltaTime, DirectionEnum dir) {
  float speed = CAMERA_SPEED * deltaTime;
  switch (dir) {
    case FORWARD:
      pos += front * speed;
      break;
    case BACK:
      pos -= front * speed;
      break;
    case LEFT:
      pos -= glm::normalize(glm::cross(front, up)) * speed;
      break;
    case RIGHT:
      pos += glm::normalize(glm::cross(front, up)) * speed;
      break;
  }
  UpdateView();
}
