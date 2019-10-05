//File: bounding_box.h
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <vector>

#include "../param.h"
#include "../ray.h"

bool _are_intersecting(std::vector<double> t_1, std::vector<double> t_2);

class BoundingBox {
  private:
    std::vector<double> _compute_t_x(Ray ray);
    std::vector<double> _compute_t_y(Ray ray);
    std::vector<double> _compute_t_z(Ray ray);

  public:
    BoundingBox();
    BoundingBox(
      double x_min_, double x_max_, double y_min_, double y_max_, double z_min_,
      double z_max_
    );
    BoundingBox(const BoundingBox &bounding_box);             // copy constructor
    BoundingBox & operator=(const BoundingBox &bounding_box); // assignment
    bool is_intersection(Ray ray);
    bool is_inside(glm::vec3 position);

    double x_min, x_max, y_min, y_max, z_min, z_max;
};

#endif
