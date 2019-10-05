//File: grid.h
#ifndef GRID_H
#define GRID_H

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "../../geometry/primitive.h"
#include "../../ray.h"
#include "../../util/vector_util.h"
#include "../bounding_box.h"
#include "cell.h"

class Grid {

  private:
    void _build_cell_array();
    void _insert_objects();
    bool _is_inside(glm::vec3 position);
    std::tuple<bool, glm::vec3, Primitive*> _find_nearest_intersection(
      Ray ray, double min_distance, bool early_break,
      std::vector<Primitive*> object_array_, unsigned int tid
    );

    double x_min, x_max, y_min, y_max, z_min, z_max, cell_size_x, cell_size_y,\
      cell_size_z;
    int n_cell_x, n_cell_y, n_cell_z;
    std::vector<std::vector<std::vector<Cell*>>> cell_array;
    BoundingBox world_bounding_box;
    std::vector<Primitive*> object_array;

  public:
    Grid();
    Grid(
      double x_min_, double x_max_, double y_min_, double y_max_,
      double z_min_, double z_max_, unsigned int n_cell_x_, unsigned int n_cell_y_,
      unsigned int n_cell_z_, std::vector<Primitive*> object_array_
    );
    std::vector<unsigned int> find_cell_address(glm::vec3 position);
    std::tuple<bool, glm::vec3, Primitive*> do_traversal(
      Ray ray, double min_distance, bool early_break, unsigned int tid);

};

#endif
