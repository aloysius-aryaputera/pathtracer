//File: triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <variant>
#include <vector>

#include <glm/vec3.hpp>

#include "../model/bounding_box.h"
#include "../material.h"
#include "../param.h"
#include "../ray.h"
#include "../util/vector_util.h"
#include "primitive.h"

class Triangle: public Primitive {
  private:
    void _compute_derived_parameters();
    void _compute_bounding_box();
    void _set_ray_intersection_parameters();

    glm::vec3 point_1, point_2, point_3, normal, point_1_trans, \
      point_2_trans, point_3_trans;
    glm::vec3 point_1_tex, point_2_tex, point_3_tex;
    glm::mat4 trans_matrix;
    Material* material;
    double area;
    BoundingBox *bounding_box;
    std::vector<glm::vec3> ray_intersection_point_array;
    std::vector<int> ray_id_array;

  public:
    Triangle();
    Triangle(const Triangle &original_triangle);             // copy constructor
    Triangle & operator=(const Triangle &original_triangle); // assignment

    void set_parameters(
      std::vector<std::variant<glm::vec3, double, Material*,
      glm::mat4>> parameter_array);
    std::vector<glm::vec3> find_nearest_intersection(Ray ray);
    glm::vec3 get_normal(glm::vec3 point_on_surface);
    Material* get_material();
    glm::vec4 get_mat_diffuse(glm::vec3 point_on_surface);
    BoundingBox* get_bounding_box();
    glm::vec3 get_ray_intersection_point(int tid, Ray ray);
    void set_ray_intersection_point(glm::vec3 intersection_point, int tid);
    void set_ray_id(Ray ray, int tid);
    int get_ray_id(int tid);

};

double _compute_triangle_area(
  glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3);
std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> \
prepare_triangle_parameters(
  glm::vec3 point_1_, glm::vec3 point_2_, glm::vec3 point_3_,
  glm::vec3 point_1_tex_, glm::vec3 point_2_tex_, glm::vec3 point_3_tex_,
  Material* material_, glm::mat4 trans_matrix_
);

#endif
