//File: cell.h
#ifndef CELL_H
#define CELL_H

#include <vector>

#include "../../geometry/primitive.h"
#include "../../ray.h"
#include "../bounding_box.h"

class Cell {
  private:
    BoundingBox* bounding_box;

  public:
    Cell();
    Cell(double x_min, double x_max, double y_min, double y_max, double z_min,
         double z_max, unsigned int i_address_, unsigned int j_address_,
         unsigned int k_address_
       );
    bool are_intersecting(BoundingBox* another_bounding_box);
    void add_object(Primitive* object);
    BoundingBox* get_bounding_box();

    unsigned int i_address, j_address, k_address;
    std::vector<Primitive*> object_array;
};

#endif
