#include "camera.h"

Camera::Camera(
  glm::vec3 eye_, glm::vec3 center_, glm::vec3 up_, double fovy_, int width_,
  int height_
) {
  eye = eye_;
  center = center_;
  up = up_;
  width = width_;
  height = height_;
  fovy = fovy_;
  fovx = 2 * atan((1.0 * width / height) * tan(M_PI * fovy / 180 / 2)) * 180 / M_PI;
  w = normalize(eye - center);
	u = normalize(cross(up, w));
	v = cross(w, u);
}

Ray Camera::compute_ray(double i, double j) {
  glm::vec3 dir;
  double alpha, beta;
  alpha = tan(fovx * M_PI / 180.0 / 2) * (j - (1.0 * width / 2)) / (1.0 * width / 2);
  beta = tan(fovy * M_PI / 180.0 / 2) * ((1.0 * height / 2) - i) / (1.0 * height / 2);
  dir = normalize(
    glm::vec3(alpha * u.x, alpha * u.y, alpha * u.z) +
    glm::vec3(beta * v.x, beta * v.y, beta * v.z) - w);
  Ray out = Ray(eye, dir);
  return out;
}
