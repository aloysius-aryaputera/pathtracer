#include "grid.h"

int num_ray_intersection_tests = 0;
int num_ray_intersections = 0;

Grid::Grid() {

}

Grid::Grid(
  double x_min_, double x_max_, double y_min_, double y_max_,
  double z_min_, double z_max_, int n_cell_x_, int n_cell_y_,
  int n_cell_z_, std::vector<Primitive*> object_array_
) {
  x_min = x_min_;
  x_max = x_max_;
  y_min = y_min_;
  y_max = y_max_;
  z_min = z_min_;
  z_max = z_max_;
  object_array = object_array_;

  n_cell_x = n_cell_x_;
  n_cell_y = n_cell_y_;
  n_cell_z = n_cell_z_;

  cell_size_x = (x_max - x_min) / n_cell_x_;
  cell_size_y = (y_max - y_min) / n_cell_y_;
  cell_size_z = (z_max - z_min) / n_cell_z_;

  _build_cell_array();
  _insert_objects();

  world_bounding_box = BoundingBox(x_min, x_max, y_min, y_max, z_min, z_max);
}

void Grid::_build_cell_array() {
  cell_array.resize(n_cell_x);
  double cell_x_min, cell_x_max, cell_y_min, cell_y_max, cell_z_min, cell_z_max;
	for (int i = 0 ; i < n_cell_x ; i++) {
    cell_array[floor(i)].resize(n_cell_y);
    for (int j = 0 ; j < n_cell_y ; j++) {
      cell_array[floor(i)][floor(j)].resize(n_cell_z);
      for (int k = 0; k < n_cell_z; k++) {

        cell_x_min = x_min + i * cell_size_x;
        cell_x_max = cell_x_min + cell_size_x;

        cell_y_min = y_min + j * cell_size_y;
        cell_y_max = cell_y_min + cell_size_y;

        cell_z_min = z_min + k * cell_size_z;
        cell_z_max = cell_z_min + cell_size_z;

        cell_array[floor(i)][floor(j)][floor(k)] = \
          new Cell(cell_x_min, cell_x_max, cell_y_min, cell_y_max, cell_z_min,
                   cell_z_max, floor(i), floor(j), floor(k));
      }
    }
  }
}

void Grid::_insert_objects() {
  printf("================================================================\n");
  printf("Inserting objects into the grid\n");
  printf("================================================================\n");
  for (int i = 0 ; i < n_cell_x ; i++) {
    for (int j = 0 ; j < n_cell_y ; j++) {
      for (int k = 0; k < n_cell_z; k++) {
        int cell_num_object = 0;
        for (int l = 0; l < object_array.size(); l++) {
          bool intersecting = \
            cell_array[floor(i)][floor(j)][floor(k)] -> are_intersecting(
              object_array[l] -> get_bounding_box());
          if (intersecting) {
            cell_array[floor(i)][floor(j)][floor(k)] -> add_object(object_array[l]);
            cell_num_object++;
          }
        }
      }
    }
  }
  printf("\n");
}

bool Grid::_is_inside(glm::vec3 position) {
  return world_bounding_box.is_inside(position);
}

std::vector<int> Grid::find_cell_address(glm::vec3 position) {
  std::vector<int> address;
  int cell_address_i, cell_address_j, cell_address_k;
  if (!_is_inside(position)) {
    printf("The position is not inside the grid!");
    throw std::string("The position is not inside the grid!");
  }
  cell_address_i = floor(((double)position.x - x_min) / cell_size_x);
  cell_address_j = floor(((double)position.y - y_min) / cell_size_y);
  cell_address_k = floor(((double)position.z - z_min) / cell_size_z);
  address.push_back(cell_address_i);
  address.push_back(cell_address_j);
  address.push_back(cell_address_k);
  return address;
}

std::tuple<bool, glm::vec3, Primitive*> Grid::do_traversal(
  Ray ray, double min_distance, bool early_break, int tid
) {

  std::vector<Primitive*> relevant_object_array;
  std::vector<int> initial_address = find_cell_address(ray.p0);
  Cell* initial_cell = cell_array[
    initial_address[0]][initial_address[1]][initial_address[2]];
  Cell* current_cell;
  double o_x, o_y, o_z, t_x_0, t_y_0, t_z_0, d_t_x, d_t_y, d_t_z, t_x, t_y, t_z;
  int i, j, k;
  std::tuple<bool, glm::vec3, Primitive*> current_intersection_tuple = \
    std::make_tuple(false, glm::vec3(0, 0, 0), nullptr);
  bool intersection_found;
  glm::vec3 current_intersection_point, best_intersection_point;

  o_x = ray.p0.x - initial_cell -> get_bounding_box() -> x_min;
  o_y = ray.p0.y - initial_cell -> get_bounding_box() -> y_min;
  o_z = ray.p0.z - initial_cell -> get_bounding_box() -> z_min;

  if (ray.dir.x < 0) {
    t_x_0 = o_x / std::fabs(ray.dir.x);
  } else {
    t_x_0 = (cell_size_x - o_x) / std::fabs(ray.dir.x);
  }
  d_t_x = cell_size_x / std::fabs(ray.dir.x);

  if (ray.dir.y < 0) {
    t_y_0 = o_y / std::fabs(ray.dir.y);
  } else {
    t_y_0 = (cell_size_y - o_y) / std::fabs(ray.dir.y);
  }
  d_t_y = cell_size_y / std::fabs(ray.dir.y);

  if (ray.dir.z < 0) {
    t_z_0 = o_z / std::fabs(ray.dir.z);
  } else {
    t_z_0 = (cell_size_z - o_z) / std::fabs(ray.dir.z);
  }
  d_t_z = cell_size_z / std::fabs(ray.dir.z);

  t_x = t_x_0;
  t_y = t_y_0;
  t_z = t_z_0;
  i = initial_cell -> i_address;
  j = initial_cell -> j_address;
  k = initial_cell -> k_address;

  while(
    i < n_cell_x && j < n_cell_y && k < n_cell_z && i >= 0 && j >= 0 && k >= 0
  ) {

    current_cell = cell_array[i][j][k];

    current_intersection_tuple = _find_nearest_intersection(
      ray, min_distance, early_break, current_cell -> object_array, tid
    );

    if (t_x <= t_y && t_x <= t_z) {
      t_x += d_t_x;
      i += (int)(ray.dir.x / std::fabs(ray.dir.x));
    } else {
      if (t_y <= t_x && t_y <= t_z) {
        t_y += d_t_y;
        j += (int)(ray.dir.y / std::fabs(ray.dir.y));
      } else {
        if (t_z <= t_x && t_z <= t_y) {
          t_z += d_t_z;
          k += (int)(ray.dir.z / std::fabs(ray.dir.z));
        }
      }
    }

    intersection_found = std::get<0>(current_intersection_tuple);
    if (intersection_found) {
      if (early_break) {
        num_ray_intersections++;
        return std::make_tuple(
           std::get<0>(current_intersection_tuple),
           std::get<1>(current_intersection_tuple),
           std::get<2>(current_intersection_tuple)
        );
      } else {
        current_intersection_point = std::get<1>(current_intersection_tuple);
        if (current_cell -> get_bounding_box() -> is_inside(current_intersection_point)) {
            num_ray_intersections++;
            return std::make_tuple(
               std::get<0>(current_intersection_tuple),
               std::get<1>(current_intersection_tuple),
               std::get<2>(current_intersection_tuple)
            );
        }
      }
    }
  }

  std::tuple<bool, glm::vec3, Primitive*> intersection_tuple_ref = \
    std::make_tuple(false, glm::vec3(0, 0, 0), nullptr);

  return intersection_tuple_ref;

}

std::tuple<bool, glm::vec3, Primitive*> Grid::_find_nearest_intersection(
  Ray ray, double min_distance, bool early_break,
  std::vector<Primitive*> object_array_, int tid
) {
  bool object_found = false;
  double distance;
  glm::vec3 intersection_point, new_intersection_point;
  Primitive* nearest_object = nullptr;
  int ray_id;

  for (int i = 0; i < object_array_.size(); i++) {
    std::vector<glm::vec3> intersect_array;
    ray_id = object_array_[i] -> get_ray_id(tid);
    new_intersection_point = object_array_[i] -> get_ray_intersection_point(
      tid, ray);
    num_ray_intersection_tests++;
    if (ray_id != ray.id) {
      object_array_[i] -> set_ray_id(ray, tid);
      intersect_array = object_array_[i] -> find_nearest_intersection(ray);
    } else {
      if (new_intersection_point != glm::vec3(INFINITY, INFINITY, INFINITY)) {
        intersect_array.push_back(new_intersection_point);
      }
    }

    if (intersect_array.size() > 0) {
      object_array_[i] -> set_ray_intersection_point(intersect_array[0], tid);
      distance = compute_distance(ray.p0, intersect_array[0]);
      if (distance < min_distance) {
        object_found = true;
        nearest_object = object_array_[i];
        min_distance = distance;
        intersection_point = glm::vec3(
          intersect_array[0].x, intersect_array[0].y, intersect_array[0].z);
        if (early_break) {
          break;
        }
      }
    }
  }

  return std::make_tuple(
    object_found, intersection_point, nearest_object);
}
