//File: light.h
#ifndef LIGHT_H
#define LIGHT_H

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include "geometry/primitive.h"
#include "material.h"
#include "param.h"

class Light {
  private:
    void _compute_derived_parameters();

  public:
    Light();
    Light(
      glm::vec4 position_, glm::vec4 colour_, glm::vec3 attenuation_);
    void set_parameters(
      glm::vec4 position_, glm::vec4 colour_, glm::vec3 attenuation_);
    glm::vec4 computelight(
      glm::vec3 seer_position, glm::vec3 point_on_surface, glm::vec3 normal,
      Primitive* object) ;
    glm::vec3 attenuation;
    glm::vec3 position_vec3;
    glm::vec4 position, colour;
};

#endif
