#include <chrono>
#include <iostream>
#include <vector>

#include <glm/vec3.hpp>

#include "geometry/primitive.h"
#include "lib_scene.h"
#include "light.h"
#include "model/camera.h"
#include "model/scene.h"
#include "param.h"
#include "render/pathtracing.h"

int main() {

  using Time = std::chrono::high_resolution_clock;
  using fsec = std::chrono::duration<float>;

  auto t0 = Time::now();

  Scene* my_scene = create_scene_2();

  pathtrace_parallel(my_scene, 8, 2, 1024);

  auto t1 = Time::now();
  fsec fs = t1 - t0;

  printf("\n");
  printf("Render time          = %5.2f sec\n", fs.count());
  printf("# primitives         = %lu\n", my_scene -> object_array.size());
  printf("# primary rays       = %u\n", num_primary_rays);
  printf("# intersection tests = %u\n", num_ray_intersection_tests);
  printf("# intersections      = %u\n", num_ray_intersections);
  printf("Efficiency           = %5.2f %%\n",
         100.0 * num_ray_intersections / num_ray_intersection_tests);

  return 0;
}
