//File: geom_util.h
#ifndef GEOM_UTIL_H
#define GEOM_UTIL_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <glm/vec3.hpp>

#include "../geometry/primitive.h"

double double_rand();
double double_rand(double min, double max);
void add_to_geom_array(
  std::vector<Primitive*>& main_array, std::vector<Primitive*> additional_array
);

#endif
