//File: scene.h
#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <glm/vec3.hpp>

#include "../geometry/primitive.h"
#include "../light.h"
#include "camera.h"
#include "grid/cell.h"
#include "grid/grid.h"

class Scene {
  private:
    void _compute_derived_parameters();
    void _compute_grid_resolutions();
    void _compute_scene_boundaries();
    void _print_scene_details();

    double x_min, x_max, y_min, y_max, z_min, z_max, d_x, d_y, d_z, volume;

  public:
    Scene(
      Camera* camera_, std::vector<Primitive*> object_array_,
      std::vector<Light*> light_array_);

    Camera* camera;
    std::vector<Primitive*> object_array;
    std::vector<Light*> light_array;
    unsigned int num_object, num_light, n_cell_x, n_cell_y, n_cell_z;
    Grid* grid;

};

#endif
