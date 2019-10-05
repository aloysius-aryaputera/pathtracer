//File: primitive.h
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <variant>
#include <vector>

#include <glm/vec3.hpp>

#include "../material.h"
#include "../model/bounding_box.h"
#include "../ray.h"

class Primitive {

  public:
    Primitive() {

    }

    virtual ~Primitive() {

    }

    virtual void set_parameters(
      std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> parameter_array) {

      }

    virtual std::vector<glm::vec3> find_nearest_intersection(Ray ray) {
      std::vector<glm::vec3> out;
      return out;
    }

    virtual glm::vec3 get_normal(glm::vec3 point_on_surface) {
      return glm::vec3(0, 0, 0);
    }

    virtual Material* get_material() {
      Material* dummy_material = new Material();
      return dummy_material;
    }

    virtual glm::vec4 get_mat_diffuse(glm::vec3 point_on_surface) {
      return glm::vec4(0, 0, 0, 1);
    }

    virtual BoundingBox* get_bounding_box() {
      BoundingBox* dummy_bounding_box = new BoundingBox();
      return dummy_bounding_box;
    }

    virtual glm::vec3 get_ray_intersection_point(unsigned int tid, Ray ray) {
      return glm::vec3(INFINITY, INFINITY, INFINITY);
    }

    virtual int get_ray_id(unsigned int tid) {
      return 0;
    }

    virtual void set_ray_intersection_point(
      glm::vec3 intersection_point, unsigned int tid) {

    }

    virtual void set_ray_id(Ray ray, unsigned int tid) {

    }
};

#endif
