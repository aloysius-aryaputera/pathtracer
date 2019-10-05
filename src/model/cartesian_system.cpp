#include "cartesian_system.h"

CartesianSystem::CartesianSystem(glm::vec3 new_z_axis_) {
  new_z_axis = new_z_axis_;
  if (std::fabs(new_z_axis.x) > std::fabs(new_z_axis.y)) {
    new_x_axis = glm::vec3(new_z_axis.z, 0, -new_z_axis.x) / \
      sqrtf(new_z_axis.x * new_z_axis.x + new_z_axis.z * new_z_axis.z);
  } else {
    new_x_axis = glm::vec3(0, -new_z_axis.z, new_z_axis.y) / \
      sqrtf(new_z_axis.y * new_z_axis.y + new_z_axis.z * new_z_axis.z);
  }
  new_y_axis = glm::normalize(glm::cross(new_z_axis, new_x_axis));
}

glm::vec3 CartesianSystem::to_world_system(glm::vec3 input_vector) {
  glm::vec3 v3_rand_world = glm::normalize(
    glm::vec3(
      input_vector.x * new_x_axis.x + input_vector.y * new_y_axis.x + \
      input_vector.z * new_z_axis.x,
      input_vector.x * new_x_axis.y + input_vector.y * new_y_axis.y + \
      input_vector.z * new_z_axis.y,
      input_vector.x * new_x_axis.z + input_vector.y * new_y_axis.z + \
      input_vector.z * new_z_axis.z
    )
  );
  return v3_rand_world;
}
