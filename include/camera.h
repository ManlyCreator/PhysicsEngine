#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CAMERA_SPEED 10.0f

typedef enum { FORWARD, BACK, LEFT, RIGHT } DirectionEnum;

class Camera {
  private:
    float yaw, pitch;
    glm::vec3 pos, front, up;
    glm::mat4 view;
    void UpdateView();
  public:
    Camera(glm::vec3 pos);
    void ProcessCursor(float deltaX, float deltaY);
    void ProcessKeyboard(float deltaTime, DirectionEnum dir);
    glm::mat4 GetView() { return view; };
};

#endif
