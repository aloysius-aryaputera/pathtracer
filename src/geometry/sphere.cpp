#include "sphere.h"

std::vector<double> _get_roots(double a, double b, double c) {
  std::vector<double> root_array;
  double discriminant;
  double root;
  discriminant = _get_discriminant(a, b, c);
  if (discriminant == 0) {
    root = -b / (2 * a);
    if (root > SMALL_DOUBLE) {
      root_array.push_back(root);
    }
  }
  if (discriminant > 0) {
    root = (-b - sqrt(discriminant)) / (2 * a);
    if (root > SMALL_DOUBLE) {
      root_array.push_back(root);
    }

    root = (-b + sqrt(discriminant)) / (2 * a);
    if (root > SMALL_DOUBLE) {
      root_array.push_back(root);
    }
  }
  return root_array;
}

double _get_discriminant(double a, double b, double c) {
  return b * b - 4 * a * c;
}

std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> \
prepare_sphere_parameters(
  glm::vec3 center_, double r_, Material* material_, glm::mat4 trans_matrix_
) {
  std::vector<
    std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array;
  parameter_array.push_back(center_);
  parameter_array.push_back(r_);
  parameter_array.push_back(material_);
  parameter_array.push_back(trans_matrix_);
  return parameter_array;
}

Sphere::Sphere() {
  center = glm::vec3(0, 0, 0);
  r = 1;
  trans_matrix = glm::mat4(1);
  _compute_bounding_box();
}

void Sphere::_compute_bounding_box() {
  double x_min, x_max, y_min, y_max, z_min, z_max, delta;
  glm::vec3 point_1, point_2, point_3, point_4, point_5, point_6, point_7, \
    point_8;
  glm::vec3 point_1_trans, point_2_trans, point_3_trans, point_4_trans,
    point_5_trans, point_6_trans, point_7_trans, point_8_trans;

  point_1 = glm::vec3(center.x - r, center.y - r, center.z - r);
  point_2 = glm::vec3(center.x - r, center.y - r, center.z + r);
  point_3 = glm::vec3(center.x - r, center.y + r, center.z - r);
  point_4 = glm::vec3(center.x - r, center.y + r, center.z + r);
  point_5 = glm::vec3(center.x + r, center.y - r, center.z - r);
  point_6 = glm::vec3(center.x + r, center.y - r, center.z + r);
  point_7 = glm::vec3(center.x + r, center.y + r, center.z - r);
  point_8 = glm::vec3(center.x + r, center.y + r, center.z + r);

  point_1_trans = transform_vec3(trans_matrix, point_1);
  point_2_trans = transform_vec3(trans_matrix, point_2);
  point_3_trans = transform_vec3(trans_matrix, point_3);
  point_4_trans = transform_vec3(trans_matrix, point_4);
  point_5_trans = transform_vec3(trans_matrix, point_5);
  point_6_trans = transform_vec3(trans_matrix, point_6);
  point_7_trans = transform_vec3(trans_matrix, point_7);
  point_8_trans = transform_vec3(trans_matrix, point_8);

  x_min = std::min((double)point_1_trans.x, (double)point_2_trans.x);
  x_min = std::min(x_min, (double)point_3_trans.x);
  x_min = std::min(x_min, (double)point_4_trans.x);
  x_min = std::min(x_min, (double)point_5_trans.x);
  x_min = std::min(x_min, (double)point_6_trans.x);
  x_min = std::min(x_min, (double)point_7_trans.x);
  x_min = std::min(x_min, (double)point_8_trans.x);

  x_max = std::max((double)point_1_trans.x, (double)point_2_trans.x);
  x_max = std::max(x_max, (double)point_3_trans.x);
  x_max = std::max(x_max, (double)point_4_trans.x);
  x_max = std::max(x_max, (double)point_5_trans.x);
  x_max = std::max(x_max, (double)point_6_trans.x);
  x_max = std::max(x_max, (double)point_7_trans.x);
  x_max = std::max(x_max, (double)point_8_trans.x);

  y_min = std::min((double)point_1_trans.y, (double)point_2_trans.y);
  y_min = std::min(y_min, (double)point_3_trans.y);
  y_min = std::min(y_min, (double)point_4_trans.y);
  y_min = std::min(y_min, (double)point_5_trans.y);
  y_min = std::min(y_min, (double)point_6_trans.y);
  y_min = std::min(y_min, (double)point_7_trans.y);
  y_min = std::min(y_min, (double)point_8_trans.y);

  y_max = std::max((double)point_1_trans.y, (double)point_2_trans.y);
  y_max = std::max(y_max, (double)point_3_trans.y);
  y_max = std::max(y_max, (double)point_4_trans.y);
  y_max = std::max(y_max, (double)point_5_trans.y);
  y_max = std::max(y_max, (double)point_6_trans.y);
  y_max = std::max(y_max, (double)point_7_trans.y);
  y_max = std::max(y_max, (double)point_8_trans.y);

  z_min = std::min((double)point_1_trans.z, (double)point_2_trans.z);
  z_min = std::min(z_min, (double)point_3_trans.z);
  z_min = std::min(z_min, (double)point_4_trans.z);
  z_min = std::min(z_min, (double)point_5_trans.z);
  z_min = std::min(z_min, (double)point_6_trans.z);
  z_min = std::min(z_min, (double)point_7_trans.z);
  z_min = std::min(z_min, (double)point_8_trans.z);

  z_max = std::max((double)point_1_trans.z, (double)point_2_trans.z);
  z_max = std::max(z_max, (double)point_3_trans.z);
  z_max = std::max(z_max, (double)point_4_trans.z);
  z_max = std::max(z_max, (double)point_5_trans.z);
  z_max = std::max(z_max, (double)point_6_trans.z);
  z_max = std::max(z_max, (double)point_7_trans.z);
  z_max = std::max(z_max, (double)point_8_trans.z);

  delta = SMALL_DOUBLE;

  bounding_box = new BoundingBox(
    x_min - delta, x_max + delta, y_min - delta, y_max + delta, z_min - delta,
    z_max + delta);
}

void Sphere::_set_ray_intersection_parameters() {
  ray_id_array.resize(10);
  ray_intersection_point_array.resize(10);
}

glm::vec3 Sphere::get_ray_intersection_point(int tid, Ray ray) {
  if (ray_id_array[tid] == ray.id) {
    return ray_intersection_point_array[tid];
  } else {
    return glm::vec3(INFINITY, INFINITY, INFINITY);
  }
}

int Sphere::get_ray_id(int tid) {
  return ray_id_array[tid];
}

void Sphere::set_ray_intersection_point(glm::vec3 intersection_point, int tid) {
  ray_intersection_point_array[tid] = intersection_point;
}

void Sphere::set_ray_id(Ray ray, int tid) {
  ray_id_array[tid] = ray.id;
  ray_intersection_point_array[tid] = glm::vec3(INFINITY, INFINITY, INFINITY);
}

void Sphere::set_parameters(
  std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array
) {
  center = std::get<glm::vec3>(parameter_array[0]);
  r = std::get<double>(parameter_array[1]);
  material = std::get<Material*>(parameter_array[2]);
  trans_matrix = std::get<glm::mat4>(parameter_array[3]);
  _compute_bounding_box();
  _set_ray_intersection_parameters();
}

Sphere::Sphere(const Sphere &original_sphere) {
  center = original_sphere.center;
  r = original_sphere.r;
  material = original_sphere.material;
  trans_matrix = original_sphere.trans_matrix;
  _compute_bounding_box();
  _set_ray_intersection_parameters();
}      // copy constructor

Sphere & Sphere::operator=(const Sphere &original_sphere) {
  if (this == &original_sphere) return *this;
  else {
    center = original_sphere.center;
    r = original_sphere.r;
    material = original_sphere.material;
    trans_matrix = original_sphere.trans_matrix;
    _compute_bounding_box();
    _set_ray_intersection_parameters();
  }
  return *this;
} // assignment

Material* Sphere::get_material() {
  return material;
}

BoundingBox* Sphere::get_bounding_box() {
  return bounding_box;
}

glm::vec3 Sphere::get_normal(glm::vec3 point_on_surface) {
  glm::vec4 point_on_surface_trans = glm::inverse(trans_matrix) * \
    glm::vec4(point_on_surface, 1);
  glm::vec4 dist_vec4 = point_on_surface_trans - glm::vec4(center, 1);
  dist_vec4 = glm::transpose(glm::inverse(trans_matrix)) * dist_vec4;
  glm::vec3 dist = glm::vec3(dist_vec4.x, dist_vec4.y, dist_vec4.z);
  return normalize(dist);
}

std::vector<glm::vec3> Sphere::find_nearest_intersection(Ray ray) {
  std::vector<glm::vec3> intersection_array;
  std::vector<double> root_array;
  glm::vec3 dir, final_intersection;
  glm::vec4 vec1, intersection;
  glm::vec4 ray_dir_trans = glm::inverse(trans_matrix) * glm::vec4(ray.dir, 0);
  glm::vec4 ray_center_trans = glm::inverse(trans_matrix) * glm::vec4(ray.p0, 1);
  glm::vec4 center_vec4 = glm::vec4(center, 1);
  double a, b, c, t;

  a = glm::dot(ray_dir_trans, ray_dir_trans);
  vec1 = ray_center_trans - center_vec4;
  b = 2 * glm::dot(ray_dir_trans, vec1);
  c = (pow(vec1.x, 2) + pow(vec1.y, 2) + pow(vec1.z, 2) + pow(vec1.w, 2)) - \
    pow(r, 2);

  root_array = _get_roots(a, b, c);
  if (root_array.size() > 0) {
    t = root_array[0];
    intersection = ray_center_trans + glm::vec4(
      t * ray_dir_trans.x, t * ray_dir_trans.y, t * ray_dir_trans.z,
      t * ray_dir_trans.w
    );
    intersection = trans_matrix * intersection;
    final_intersection = glm::vec3(
      intersection.x / intersection.w, intersection.y / intersection.w,
      intersection.z / intersection.w
    );

    intersection_array.push_back(final_intersection);
  }
  return intersection_array;
}

glm::vec4 Sphere::get_mat_diffuse(glm::vec3 point_on_surface) {
  // Reference: https://en.wikipedia.org/wiki/UV_mapping
  glm::vec3 dir_from_center = normalize(- point_on_surface + center);
  double u, v;
  if (material -> has_texture()) {
    u = 0.5 + atan2(dir_from_center.z, dir_from_center.x) / (2 * M_PI);
    v = 0.5 - asin(dir_from_center.y) / M_PI;
  }
  return material -> get_diffuse(u, v);
}
