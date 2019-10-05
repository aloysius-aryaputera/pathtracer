//File: material.h
#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>
#include <iostream>
#include <vector>

#include <glm/vec4.hpp>

#include "util/image_util.h"

class Material {
  private:
    std::vector<std::vector<glm::vec4>> texture;
    glm::vec4 ambient, diffuse, specular, emission, albedo;
    double shininess;
    glm::vec4 _get_point_texture(double u, double v);

  public:
    Material();
    Material(
      glm::vec4 ambient_, glm::vec4 diffuse_, glm::vec4 specular_,
      glm::vec4 emission_, glm::vec4 albedo, double shininess_,
      std::vector<std::vector<glm::vec4>> texture_
    );
    Material(const Material &original_material);             // copy constructor
    Material & operator=(const Material &original_material); // assignment
    bool is_reflective();
    bool has_texture();
    glm::vec4 get_albedo();
    glm::vec4 get_ambient();
    glm::vec4 get_diffuse(double u, double v);
    glm::vec4 get_specular();
    glm::vec4 get_emission();
    double get_shininess();
};

#endif
