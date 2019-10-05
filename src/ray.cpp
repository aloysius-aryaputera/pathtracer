#include "ray.h"

Ray::Ray(glm::vec3 p0_, glm::vec3 dir_) {
  p0 = p0_;
  dir = glm::normalize(dir_);
  id = rand();
}

glm::vec3 Ray::get_vector(double t) {
  return p0 + glm::vec3(t * dir.x, t * dir.y, t * dir.z);
}
