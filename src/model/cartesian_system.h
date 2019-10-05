//File: cartesian_system.h
#ifndef CARTESIAN_SYSTEM_H
#define CARTESIAN_SYSTEM_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class CartesianSystem {

  public:
    CartesianSystem(glm::vec3 new_z_axis_);
    glm::vec3 to_world_system(glm::vec3 input_vector);
    glm::vec3 new_x_axis, new_y_axis, new_z_axis;
};

#endif
