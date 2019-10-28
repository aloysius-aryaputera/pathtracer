//File: pathtracing.h
#ifndef PATHTRACING_H
#define PATHTRACING_H

#include <cmath>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <tuple>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../geometry/primitive.h"
#include "../geometry/sphere.h"
#include "../light.h"
#include "../model/camera.h"
#include "../model/cartesian_system.h"
#include "../model/scene.h"
#include "../param.h"
#include "../util/geom_util.h"
#include "../util/image_util.h"
#include "../util/vector_util.h"

glm::vec3 _get_random_vector();
glm::vec4 _find_colour_pathtracing(
  glm::vec3 seer_position, glm::vec3 point_on_surface, Primitive* object,
  Scene* scene, int indirect_diffuse_level, int reflection_level,
  int sampling_size, int tid
);
glm::vec4 _compute_indirect_diffuse(
  glm::vec3 point_on_surface, Primitive* object, Scene* scene,
  int indirect_diffuse_level, int reflection_level, int sampling_size,
  int tid
);
glm::vec4 _compute_direct_lighting(
  glm::vec3 seer_position, glm::vec3 point_on_surface, Light* light,
  Primitive* object, std::vector<Primitive*> object_array, Scene* scene,
  int tid
);
glm::vec4 _compute_reflection(
  glm::vec3 seer_position, glm::vec3 point_on_surface, Primitive* object,
  Scene* scene, int indirect_diffuse_level, int reflection_level,
  int sampling_size, int tid
);
void pathtrace_parallel(
  Scene* scene, int indirect_diffuse, int reflection_level, int sampling_size
);

#endif
