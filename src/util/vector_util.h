//File: vector_util.h
#ifndef VECTOR_UTIL_H
#define VECTOR_UTIL_H

#include <iostream>
#include <math.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../param.h"
#include "geom_util.h"

void print_vec3(const glm::vec3 &v);
double compute_distance(const glm::vec3 &v1, const glm::vec3 &v2);
glm::vec3 get_random_unit_vector_hemisphere();
glm::vec3 transform_vec3(const glm::mat4 &trans_matrix, const glm::vec3 &v);
glm::mat3 rotate(const float degrees, const glm::vec3& axis);
glm::mat4 scale(const double &sx, const double &sy, const double &sz);
glm::mat4 translate(const float &tx, const float &ty, const float &tz);

#endif
