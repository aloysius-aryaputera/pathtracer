#include "geom_util.h"

double double_rand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}

double double_rand(double min, double max) {
  return min + double(rand()) / (double(RAND_MAX) + 1.0) * (max - min);
}

void add_to_geom_array(
  std::vector<Primitive*>& main_array,
  std::vector<Primitive*> additional_array
) {
  for (int i = 0; i < additional_array.size(); i++) {
    main_array.push_back(additional_array[i]);
  }
}
