#include "material.h"

Material::Material() {
  std::vector<std::vector<glm::vec4>> initial_texture;
  ambient = glm::vec4(0, 0, 0, 1);
  diffuse = glm::vec4(0, 0, 0, 1);
  specular = glm::vec4(0, 0, 0, 1);
  emission = glm::vec4(0, 0, 0, 1);
  albedo = glm::vec4(0, 0, 0, 1);
  shininess = 0;
  texture = initial_texture;
}

Material::Material(
  glm::vec4 ambient_, glm::vec4 diffuse_, glm::vec4 specular_,
  glm::vec4 emission_, glm::vec4 albedo_, double shininess_,
  std::vector<std::vector<glm::vec4>> texture_
) {
  ambient = glm::vec4(ambient_.x, ambient_.y, ambient_.z, ambient_.w);
  diffuse = glm::vec4(diffuse_.x, diffuse_.y, diffuse_.z, diffuse_.w);
  specular = glm::vec4(specular_.x, specular_.y, specular_.z, specular_.w);
  emission = glm::vec4(emission_.x, emission_.y, emission_.z, emission_.w);
  albedo = glm::vec4(albedo_.x, albedo_.y, albedo_.z, albedo_.w);
  shininess = shininess_;
  texture = texture_;
}

Material::Material(const Material &original_material) {
  ambient = glm::vec4(
    original_material.ambient.x, original_material.ambient.y,
    original_material.ambient.z, original_material.ambient.w);
  diffuse = glm::vec4(
    original_material.diffuse.x, original_material.diffuse.y,
    original_material.diffuse.z, original_material.diffuse.w);
  specular = glm::vec4(
    original_material.specular.x, original_material.specular.y,
    original_material.specular.z, original_material.specular.w);
  emission = glm::vec4(
    original_material.emission.x, original_material.emission.y,
    original_material.emission.z, original_material.emission.w);
  albedo = glm::vec4(
    original_material.albedo.x, original_material.albedo.y,
    original_material.albedo.z, original_material.albedo.w);
  shininess = original_material.shininess;
  texture = original_material.texture;
}      // copy constructor

Material & Material::operator=(const Material &original_material) {
  if (this == &original_material) return *this;
  else {
    ambient = glm::vec4(
      original_material.ambient.x, original_material.ambient.y,
      original_material.ambient.z, original_material.ambient.w);
    diffuse = glm::vec4(
      original_material.diffuse.x, original_material.diffuse.y,
      original_material.diffuse.z, original_material.diffuse.w);
    specular = glm::vec4(
      original_material.specular.x, original_material.specular.y,
      original_material.specular.z, original_material.specular.w);
    emission = glm::vec4(
      original_material.emission.x, original_material.emission.y,
      original_material.emission.z, original_material.emission.w);
    albedo = glm::vec4(
      original_material.albedo.x, original_material.albedo.y,
      original_material.albedo.z, original_material.albedo.w);
    shininess = original_material.shininess;
    texture = original_material.texture;
  }
  return *this;
} // assignment

glm::vec4 Material::_get_point_texture(double u, double v) {
  glm::vec4 point_texture;
  if (has_texture()) {
    int height = texture.size();
    int width = texture[0].size();
    u = clamp(0, 1, u);
    v = clamp(0, 1, v);
    int ver_idx = floor(u * (height - 1));
    int hor_idx = floor(v * (width - 1));
    point_texture = texture[ver_idx][hor_idx];
  }
  return point_texture;
}

bool Material::is_reflective() {
  return specular != glm::vec4(0, 0, 0, 1);
}

bool Material::has_texture() {
  return texture.size() > 0;
}

glm::vec4 Material::get_albedo() {
  return albedo;
}

glm::vec4 Material::get_ambient() {
  return ambient;
}

glm::vec4 Material::get_diffuse(double u, double v) {
  if (has_texture()) {
    return _get_point_texture(u, v);
  }
  return diffuse;
}

glm::vec4 Material::get_specular() {
  return specular;
}

glm::vec4 Material::get_emission() {
  return emission;
}

double Material::get_shininess() {
  return shininess;
}
