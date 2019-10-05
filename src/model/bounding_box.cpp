#include "bounding_box.h"

bool _are_intersecting(std::vector<double> t_1, std::vector<double> t_2) {
  double t_1_min = t_1[0];
  double t_1_max = t_1[1];
  double t_2_min = t_2[0];
  double t_2_max = t_2[1];
  return t_1_min <= t_2_max && t_2_min <= t_1_max;
}

BoundingBox::BoundingBox() {
  x_min = -INFINITY;
  x_max = INFINITY;
  y_min = -INFINITY;
  y_max = INFINITY;
  z_min = -INFINITY;
  z_max = INFINITY;
}

BoundingBox::BoundingBox(
  double x_min_, double x_max_, double y_min_, double y_max_, double z_min_,
  double z_max_
) {
  x_min = x_min_;
  x_max = x_max_;
  y_min = y_min_;
  y_max = y_max_;
  z_min = z_min_;
  z_max = z_max_;
}

BoundingBox::BoundingBox(const BoundingBox &original_bounding_box) {
  x_min = original_bounding_box.x_min;
  x_max = original_bounding_box.x_max;
  y_min = original_bounding_box.y_min;
  y_max = original_bounding_box.y_max;
  z_min = original_bounding_box.z_min;
  z_max = original_bounding_box.z_max;
}      // copy constructor

BoundingBox & BoundingBox::operator=(const BoundingBox &original_bounding_box) {
  if (this == &original_bounding_box) return *this;
  else {
    x_min = original_bounding_box.x_min;
    x_max = original_bounding_box.x_max;
    y_min = original_bounding_box.y_min;
    y_max = original_bounding_box.y_max;
    z_min = original_bounding_box.z_min;
    z_max = original_bounding_box.z_max;
  }
  return *this;
} // assignment

std::vector<double> BoundingBox::_compute_t_x(Ray ray) {
  double t1, t2, t_x_min, t_x_max;
  std::vector<double> out;
  t1 = (x_min - ray.p0.x) / ray.dir.x;
  t2 = (x_max - ray.p0.x) / ray.dir.x;
  if (t1 > t2) {
    t_x_min = t1;
    t_x_max = t2;
  } else {
    t_x_min = t2;
    t_x_max = t1;
  }
  out.push_back(t_x_min);
  out.push_back(t_x_max);
  return out;
}

std::vector<double> BoundingBox::_compute_t_y(Ray ray) {
  double t1, t2, t_y_min, t_y_max;
  std::vector<double> out;
  t1 = (y_min - ray.p0.y) / ray.dir.y;
  t2 = (y_max - ray.p0.y) / ray.dir.y;
  if (t1 > t2) {
    t_y_min = t1;
    t_y_max = t2;
  } else {
    t_y_min = t2;
    t_y_max = t1;
  }
  out.push_back(t_y_min);
  out.push_back(t_y_max);
  return out;
}

std::vector<double> BoundingBox::_compute_t_z(Ray ray) {
  double t1, t2, t_z_min, t_z_max;
  std::vector<double> out;
  t1 = (z_min - ray.p0.z) / ray.dir.z;
  t2 = (z_max - ray.p0.z) / ray.dir.z;
  if (t1 > t2) {
    t_z_min = t1;
    t_z_max = t2;
  } else {
    t_z_min = t2;
    t_z_max = t1;
  }
  out.push_back(t_z_min);
  out.push_back(t_z_max);
  return out;
}

bool BoundingBox::is_intersection(Ray ray) {
  std::vector<double> t_x, t_y, t_z;
  t_x = _compute_t_x(ray);
  t_y = _compute_t_y(ray);
  if (_are_intersecting(t_x, t_y)) {
    double t_xy_min, t_xy_max;
    std::vector<double> t_xy;
    t_xy_min = std::max(t_x[0], t_y[0]);
    t_xy_max = std::min(t_x[1], t_y[1]);
    t_xy.push_back(t_xy_min);
    t_xy.push_back(t_xy_max);
    if (_are_intersecting(t_xy, t_z)) {
      return true;
    }
  }
  return false;
}

bool BoundingBox::is_inside(glm::vec3 position) {
  if (
    position.x >= (x_min - SMALL_DOUBLE) &&
    position.x <= (x_max + SMALL_DOUBLE) &&
    position.y >= (y_min - SMALL_DOUBLE) &&
    position.y <= (y_max + SMALL_DOUBLE) &&
    position.z >= (z_min - SMALL_DOUBLE) &&
    position.z <= (z_max + SMALL_DOUBLE)
  ) {
    return true;
  } else {
    return false;
  }
}
