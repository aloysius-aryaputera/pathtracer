#include "cell.h"

Cell::Cell() {
  bounding_box = new BoundingBox();
}

Cell::Cell(
  double x_min, double x_max, double y_min, double y_max, double z_min,
  double z_max, int i_address_, int j_address_, int k_address_
) {
  bounding_box = new BoundingBox(x_min, x_max, y_min, y_max, z_min, z_max);
  i_address = i_address_;
  j_address = j_address_;
  k_address = k_address_;
}

bool Cell::are_intersecting(BoundingBox* another_bounding_box) {
  return (bounding_box -> x_min <= another_bounding_box -> x_max) && \
    (another_bounding_box -> x_min <= bounding_box -> x_max) && \
    (bounding_box -> y_min <= another_bounding_box -> y_max) && \
    (another_bounding_box -> y_min <= bounding_box -> y_max) && \
    (bounding_box -> z_min <= another_bounding_box -> z_max) && \
    (another_bounding_box -> z_min <= bounding_box -> z_max);
}

void Cell::add_object(Primitive* object) {
  object_array.push_back(object);
}

BoundingBox* Cell::get_bounding_box() {
  return bounding_box;
}
