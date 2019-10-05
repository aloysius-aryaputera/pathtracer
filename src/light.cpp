#include "light.h"

Light::Light() {
  position = glm::vec4(0, 0, 0, 1);
  colour = glm::vec4(0, 0, 0, 1);
  attenuation = glm::vec3(0, 0, 0);
  _compute_derived_parameters();
}

Light::Light(
  glm::vec4 position_, glm::vec4 colour_, glm::vec3 attenuation_
) {
  position = position_;
  colour = colour_;
  attenuation = attenuation_;
  _compute_derived_parameters();
}

void Light::set_parameters(
  glm::vec4 position_, glm::vec4 colour_, glm::vec3 attenuation_
) {
  position = position_;
  colour = colour_;
  attenuation = attenuation_;
  _compute_derived_parameters();
}

glm::vec4 Light::computelight(
  glm::vec3 seer_position, glm::vec3 point_on_surface, glm::vec3 normal,
  Primitive* object
) {

  glm::vec3 direction, eyedirn;

  if (position.w > 0) {
    eyedirn = glm::normalize(seer_position - point_on_surface) ;
    direction = glm::normalize (position_vec3 - point_on_surface) ;
  } else {
    direction = -glm::normalize (position_vec3) ;
  }
  glm::vec3 halfvec = glm::normalize (direction + eyedirn) ;

  double nDotL = dot(normal, direction)  ;
  double factor = std::max (nDotL, 0.0);
  glm::vec4 lambert = object -> get_mat_diffuse(point_on_surface) * colour;
  lambert = glm::vec4(
    factor * lambert.x, factor * lambert.y, factor * lambert.z,
    factor * lambert.w
  );

  double nDotH = dot(normal, halfvec) ;
  glm::vec4 phong = object -> get_material() -> get_specular() * colour;
  double factor2 = pow (std::max(nDotH, 0.0), object -> get_material() -> get_shininess()) ;
  phong = glm::vec4(
    factor2 * phong.x, factor2 * phong.y, factor2 * phong.z,
    factor2 * phong.w
  );

  glm::vec4 retval = lambert + phong ;

  double att_factor;
  if (position.w > 0) {
    double distance = dot(direction, direction);
    att_factor = 1 / (
      attenuation.x + attenuation.y * distance +
      attenuation.z * pow(distance, 2));
  } else {
    att_factor = 1;
  }

  glm::vec4 finalcol = glm::vec4(
    att_factor * retval.x, att_factor * retval.y, att_factor * retval.z,
    att_factor * retval.w
  );

  return finalcol;
}

void Light::_compute_derived_parameters() {
  if (position.w > 0) {
    position_vec3 = glm::vec3(
      position.x / position.w, position.y / position.w, position.z / position.w
    );
  } else {
    position_vec3 = glm::vec3(position.x, position.y, position.z);
  }
}
