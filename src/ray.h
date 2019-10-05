//File: ray.h
#ifndef RAY_H
#define RAY_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

class Ray {
  public:
    Ray(glm::vec3 p0_, glm::vec3 dir_);
    glm::vec3 get_vector(double t);
    glm::vec3 p0, dir;
    int id;
};

#endif
