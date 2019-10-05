//File: camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include "../param.h"
#include "../ray.h"

class Camera {
  public:
    Camera(
      glm::vec3 eye_, glm::vec3 center_, glm::vec3 up_, double fovy_, int width,
      int height
    );

    Ray compute_ray(double i, double j);
    glm::vec3 eye, center, up, u, v, w;
    unsigned int width, height;
    double fovy, fovx;
};

#endif
