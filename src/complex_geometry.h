//File: complex_geometry.h
#ifndef COMPLEX_GEOMETRY_H
#define COMPLEX_GEOMETRY_H

#include <variant>
#include <vector>

#include <glm/vec3.hpp>

#include "geometry/primitive.h"
#include "geometry/triangle.h"
#include "material.h"
#include "util/geom_util.h"

std::vector<Primitive*> create_rectangle(
  glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3, glm::vec3 point_4,
  glm::vec3 point_1_tex, glm::vec3 point_2_tex, glm::vec3 point_3_tex,
  glm::vec3 point_4_tex, Material* material, glm::mat4 trans_matrix
);
std::vector<Primitive*> create_box(
  glm::vec3 center, double len_x, double len_y, double len_z,
  Material* material, glm::mat4 trans_matrix
);
std::vector<Primitive*> create_rect_pyramid(
  glm::vec3 center_base, double len_base, double width_base, double height,
  Material* material, glm::mat4 trans_matrix
);

#endif
