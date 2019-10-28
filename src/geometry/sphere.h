//File: sphere.h
#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <math.h>
#include <variant>
#include <vector>

#include <glm/vec3.hpp>

#include "../model/bounding_box.h"
#include "../material.h"
#include "../param.h"
#include "../ray.h"
#include "../util/vector_util.h"
#include "primitive.h"

class Sphere: public Primitive {
  private:
    void _set_ray_intersection_parameters();

    glm::vec3 center;
    glm::mat4 trans_matrix;
    double r;
    Material* material;
    BoundingBox* bounding_box;
    void _compute_bounding_box();
    std::vector<glm::vec3> ray_intersection_point_array;
    std::vector<int> ray_id_array;

  public:
    Sphere();
    Sphere(const Sphere &original_sphere);             // copy constructor
    Sphere & operator=(const Sphere &original_sphere); // assignment

    void set_parameters(
      std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array);
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

std::vector<double> _get_roots(double a, double b, double c);
double _get_discriminant(double a, double b, double c);
std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> \
prepare_sphere_parameters(
  glm::vec3 center_, double r_, Material* material_, glm::mat4 trans_matrix_
);

#endif
