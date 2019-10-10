#include "triangle.h"

std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> \
prepare_triangle_parameters(
  glm::vec3 point_1_, glm::vec3 point_2_, glm::vec3 point_3_,
  glm::vec3 point_1_tex_, glm::vec3 point_2_tex_, glm::vec3 point_3_tex_,
  Material* material_, glm::mat4 trans_matrix_
) {
  std::vector<
    std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array;
  parameter_array.push_back(point_1_);
  parameter_array.push_back(point_2_);
  parameter_array.push_back(point_3_);
  parameter_array.push_back(point_1_tex_);
  parameter_array.push_back(point_2_tex_);
  parameter_array.push_back(point_3_tex_);
  parameter_array.push_back(material_);
  parameter_array.push_back(trans_matrix_);
  return parameter_array;
}

double _compute_triangle_area(
  glm::vec3 point_1_, glm::vec3 point_2_, glm::vec3 point_3_
) {
  double s1 = compute_distance(point_1_, point_2_);
  double s2 = compute_distance(point_1_, point_3_);
  double s3 = compute_distance(point_2_, point_3_);
  double s = (s1 + s2 + s3) / 2.0;
  return pow(s * (s - s1) * (s - s2) * (s - s3), 0.5);
}

void Triangle::_set_ray_intersection_parameters() {
  ray_id_array.resize(10);
  ray_intersection_point_array.resize(10);
}

glm::vec3 Triangle::get_ray_intersection_point(unsigned int tid, Ray ray) {
  if (ray_id_array[tid] == ray.id) {
    return ray_intersection_point_array[tid];
  } else {
    return glm::vec3(INFINITY, INFINITY, INFINITY);
  }
}

int Triangle::get_ray_id(unsigned int tid) {
  return ray_id_array[tid];
}

void Triangle::set_ray_intersection_point(
  glm::vec3 intersection_point, unsigned int tid
) {
  ray_intersection_point_array[tid] = intersection_point;
}

void Triangle::set_ray_id(Ray ray, unsigned int tid) {
  ray_id_array[tid] = ray.id;
  ray_intersection_point_array[tid] = glm::vec3(INFINITY, INFINITY, INFINITY);
}

Triangle::Triangle() {
  point_1 = glm::vec3(0, 0, 0);
  point_2 = glm::vec3(1, 0, 0);
  point_3 = glm::vec3(0, 0, 1);
  point_1_tex = glm::vec3(0, 0, 0);
  point_2_tex = glm::vec3(0, 1, 0);
  point_3_tex = glm::vec3(1, 1, 0);
  trans_matrix = glm::mat4(1);
  _compute_derived_parameters();
}

Triangle::Triangle(const Triangle &original_triangle) {
  point_1 = original_triangle.point_1;
  point_2 = original_triangle.point_2;
  point_3 = original_triangle.point_3;
  point_1_tex = original_triangle.point_1_tex;
  point_2_tex = original_triangle.point_2_tex;
  point_3_tex = original_triangle.point_3_tex;
  material = original_triangle.material;
  trans_matrix = original_triangle.trans_matrix;
  _compute_derived_parameters();
}      // copy constructor

Triangle & Triangle::operator=(const Triangle &original_triangle) {
  if (this == &original_triangle) return *this;
  else {
    point_1 = original_triangle.point_1;
    point_2 = original_triangle.point_2;
    point_3 = original_triangle.point_3;
    point_1_tex = original_triangle.point_1_tex;
    point_2_tex = original_triangle.point_2_tex;
    point_3_tex = original_triangle.point_3_tex;
    material = original_triangle.material;
    trans_matrix = original_triangle.trans_matrix;
    _compute_derived_parameters();
  }
  return *this;
} // assignment

void Triangle::set_parameters(
  std::vector<
  std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array
) {
  point_1 = std::get<glm::vec3>(parameter_array[0]);
  point_2 = std::get<glm::vec3>(parameter_array[1]);
  point_3 = std::get<glm::vec3>(parameter_array[2]);
  point_1_tex = std::get<glm::vec3>(parameter_array[3]);
  point_2_tex = std::get<glm::vec3>(parameter_array[4]);
  point_3_tex = std::get<glm::vec3>(parameter_array[5]);
  material = std::get<Material*>(parameter_array[6]);
  trans_matrix = std::get<glm::mat4>(parameter_array[7]);
  _compute_derived_parameters();
}

void Triangle::_compute_derived_parameters() {
  point_1_trans = transform_vec3(trans_matrix, point_1);
  point_2_trans = transform_vec3(trans_matrix, point_2);
  point_3_trans = transform_vec3(trans_matrix, point_3);
  normal = get_normal(point_1_trans);
  area = _compute_triangle_area(point_1_trans, point_2_trans, point_3_trans);
  _compute_bounding_box();
  _set_ray_intersection_parameters();
}

void Triangle::_compute_bounding_box() {
  double x_min, x_max, y_min, y_max, z_min, z_max, delta;

  x_min = std::min((double)point_1_trans.x, (double)point_2_trans.x);
  x_min = std::min(x_min, (double)point_3_trans.x);

  x_max = std::max((double)point_1_trans.x, (double)point_2_trans.x);
  x_max = std::max(x_max, (double)point_3_trans.x);

  y_min = std::min((double)point_1_trans.y, (double)point_2_trans.y);
  y_min = std::min(y_min, (double)point_3_trans.y);

  y_max = std::max((double)point_1_trans.y, (double)point_2_trans.y);
  y_max = std::max(y_max, (double)point_3_trans.y);

  z_min = std::min((double)point_1_trans.z, (double)point_2_trans.z);
  z_min = std::min(z_min, (double)point_3_trans.z);

  z_max = std::max((double)point_1_trans.z, (double)point_2_trans.z);
  z_max = std::max(z_max, (double)point_3_trans.z);

  delta = SMALL_DOUBLE;

  bounding_box = new BoundingBox(
    x_min - delta, x_max + delta, y_min - delta, y_max + delta, z_min - delta,
    z_max + delta);
}

glm::vec3 Triangle::get_normal(glm::vec3 point_on_surface) {
  glm::vec3 cross_product = glm::cross(
    point_2_trans - point_1_trans, point_3_trans - point_1_trans);
  return normalize(cross_product);
}

Material* Triangle::get_material() {
  return material;
}

BoundingBox* Triangle::get_bounding_box() {
  return bounding_box;
}

std::vector<glm::vec3> Triangle::find_nearest_intersection(Ray ray) {
  std::vector<glm::vec3> intersection_array;
  double t = (glm::dot(point_1_trans, normal) - glm::dot(ray.p0, normal)) / \
    glm::dot(ray.dir, normal);
  glm::vec3 point_4 = ray.get_vector(t);

  if (
    (compute_distance(point_4, point_1_trans) < SMALL_DOUBLE ||
     compute_distance(point_4, point_2_trans) < SMALL_DOUBLE ||
     compute_distance(point_4, point_3_trans) < SMALL_DOUBLE) &&
     t > SMALL_DOUBLE
    ) {
    intersection_array.push_back(point_4);
    return intersection_array;
  }

  double area_1 = _compute_triangle_area(point_1_trans, point_2_trans, point_4);
  double area_2 = _compute_triangle_area(point_1_trans, point_3_trans, point_4);
  double area_3 = _compute_triangle_area(point_2_trans, point_3_trans, point_4);

  if ((area_1 + area_2 + area_3 - area) < SMALL_DOUBLE && t > SMALL_DOUBLE) {
    intersection_array.push_back(point_4);
  }

  return intersection_array;
}

glm::vec4 Triangle::get_mat_diffuse(glm::vec3 point_on_surface) {
  double alpha, beta, gamma, u, v;
  if (material -> has_texture()) {
    if (compute_distance(point_on_surface, point_1_trans) < SMALL_DOUBLE) {
      return material -> get_diffuse(point_1_tex.x, point_1_tex.y);
    }
    if (compute_distance(point_on_surface, point_2_trans) < SMALL_DOUBLE) {
      return material -> get_diffuse(point_2_tex.x, point_2_tex.y);
    }
    if (compute_distance(point_on_surface, point_3_trans) < SMALL_DOUBLE) {
      return material -> get_diffuse(point_3_tex.x, point_3_tex.y);
    }
    alpha = _compute_triangle_area(point_on_surface, point_2_trans, point_3_trans) / area;
    beta = _compute_triangle_area(point_1_trans, point_on_surface, point_3_trans) / area;
    gamma = 1 - alpha - beta;
    u = alpha * point_1_tex.x + beta * point_2_tex.x + gamma * point_3_tex.x;
    v = alpha * point_1_tex.y + beta * point_2_tex.y + gamma * point_3_tex.y;
  }
  return material -> get_diffuse(u, v);
}
