#include "scene.h"

Scene::Scene(
  Camera* camera_, std::vector<Primitive*> object_array_,
  std::vector<Light*> light_array_
) {
  camera = camera_;
  object_array = object_array_;
  light_array = light_array_;
  _compute_derived_parameters();
  _print_scene_details();
  grid = new Grid(
    x_min, x_max, y_min, y_max, z_min, z_max, n_cell_x, n_cell_y, n_cell_z,
    object_array
  );
}

void Scene::_compute_derived_parameters() {
  num_object = object_array.size();
  num_light = light_array.size();
  _compute_scene_boundaries();
  _compute_grid_resolutions();
}

void Scene::_compute_grid_resolutions() {
  n_cell_x = (int)(d_x * pow(LAMBDA * num_object / volume, 1.0 / 3));
  n_cell_y = (int)(d_y * pow(LAMBDA * num_object / volume, 1.0 / 3));
  n_cell_z = (int)(d_z * pow(LAMBDA * num_object / volume, 1.0 / 3));
}

void Scene::_compute_scene_boundaries() {
  x_min = camera -> eye.x;
  x_max = camera -> eye.x;
  y_min = camera -> eye.y;
  y_max = camera -> eye.y;
  z_min = camera -> eye.z;
  z_max = camera -> eye.z;
  for (int i = 0; i < num_object; i++) {
    x_min = std::min(x_min, object_array[i] -> get_bounding_box() -> x_min);
    x_max = std::max(x_max, object_array[i] -> get_bounding_box() -> x_max);
    y_min = std::min(y_min, object_array[i] -> get_bounding_box() -> y_min);
    y_max = std::max(y_max, object_array[i] -> get_bounding_box() -> y_max);
    z_min = std::min(z_min, object_array[i] -> get_bounding_box() -> z_min);
    z_max = std::max(z_max, object_array[i] -> get_bounding_box() -> z_max);
  }
  for (int i = 0; i < num_light; i++) {
    if (light_array[i] -> position.w > 0) {
      x_min = std::min(x_min, (double)light_array[i] -> position.x);
      x_max = std::max(x_max, (double)light_array[i] -> position.x);
      y_min = std::min(y_min, (double)light_array[i] -> position.y);
      y_max = std::max(y_max, (double)light_array[i] -> position.y);
      z_min = std::min(z_min, (double)light_array[i] -> position.z);
      z_max = std::max(z_max, (double)light_array[i] -> position.z);
    }
  }

  x_min -= 1;
  x_max += 1;
  y_min -= 1;
  y_max += 1;
  z_min -= 1;
  z_max += 1;

  d_x = x_max - x_min;
  d_y = y_max - y_min;
  d_z = z_max - z_min;
  volume = d_x * d_y * d_z;
}

void Scene::_print_scene_details() {
  printf("================================================================\n");
  printf("Boundaries\n");
  printf("================================================================\n");
  printf("x_min = %5.2f; x_max = %5.2f, d_x = %5.2f\n", x_min, x_max, d_x);
  printf("y_min = %5.2f; y_max = %5.2f, d_y = %5.2f\n", y_min, y_max, d_y);
  printf("z_min = %5.2f; z_max = %5.2f, d_z = %5.2f\n", z_min, z_max, d_z);
  printf("\n");
  printf("================================================================\n");
  printf("Elements\n");
  printf("================================================================\n");
  printf("Number of objects       = %d\n", num_object);
  printf("Number of light sources = %d\n", num_light);
  printf("\n");
  printf("================================================================\n");
  printf("Grid\n");
  printf("================================================================\n");
  printf("x resolution = %d, y resolution = %d, z resolution = %d\n",
         n_cell_x, n_cell_y, n_cell_z);
  printf("\n");
}
