#include "pathtracing.h"

int pixel_done = 0;
int num_primary_rays = 0;

glm::vec4 _compute_indirect_diffuse(
  glm::vec3 point_on_surface, Primitive* object, Scene* scene,
  int indirect_diffuse_level, int reflection_level,
  int sampling_size, int tid
) {
  glm::vec3 normal = object -> get_normal(point_on_surface);
  CartesianSystem new_xyz_system = CartesianSystem(normal);
  double pdf = 1 / (2 * M_PI), cos_theta;
  glm::vec3 v3_rand, v3_rand_world;
  glm::vec4 sample_indirect_lighting = glm::vec4(0, 0, 0, 1);
  glm::vec4 indirect_lighting = glm::vec4(0, 0, 0, 1);
  int new_sampling_size = 1;

  for (int i = 0; i < sampling_size; i++) {

    v3_rand = get_random_unit_vector_hemisphere();
    cos_theta = v3_rand.z;
    v3_rand_world = new_xyz_system.to_world_system(v3_rand);

    Ray ray = Ray(point_on_surface, v3_rand_world);
    std::tuple<bool, glm::vec3, Primitive*> intersection_tuple = \
      scene -> grid -> do_traversal(ray, INFINITY, false, tid);
    bool intersection_found = std::get<0>(intersection_tuple);
      if (intersection_found) {
        Primitive* nearest_object = std::get<2>(intersection_tuple);
        glm::vec3 point_on_surface_2 = std::get<1>(intersection_tuple);
        sample_indirect_lighting = _find_colour_pathtracing(
          point_on_surface, point_on_surface_2, nearest_object, scene,
          indirect_diffuse_level - 1, reflection_level - 1, new_sampling_size,
          tid);
        sample_indirect_lighting = glm::vec4(
          sample_indirect_lighting.x * cos_theta,
          sample_indirect_lighting.y * cos_theta,
          sample_indirect_lighting.z * cos_theta,
          1
        );
        indirect_lighting += sample_indirect_lighting;
      }
  }
  indirect_lighting = glm::vec4(
    indirect_lighting.x / (double)sampling_size / pdf,
    indirect_lighting.y / (double)sampling_size / pdf,
    indirect_lighting.z / (double)sampling_size / pdf,
    1
  );

  return indirect_lighting * object -> get_mat_diffuse(point_on_surface);
}

glm::vec4 _compute_direct_lighting(
  glm::vec3 seer_position, glm::vec3 point_on_surface, Light* light,
  Primitive* object, std::vector<Primitive*> object_array, Scene* scene,
  int tid
) {
  glm::vec3 normal = object -> get_normal(point_on_surface);
  glm::vec3 direction;
  double dist_to_light;
  glm::vec4 colour = glm::vec4(0, 0, 0, 1);

  if (light -> position.w > 0) {
    direction = light -> position_vec3 - point_on_surface;
    dist_to_light = compute_distance(
      point_on_surface, light -> position_vec3);
  } else {
    direction = -light -> position_vec3;
    dist_to_light = INFINITY;
  }
  Ray ray = Ray(point_on_surface, direction);
  std::tuple<bool, glm::vec3, Primitive*> intersection_tuple = \
    scene -> grid -> do_traversal(ray, dist_to_light, true, tid);
  bool blockage_found = std::get<0>(intersection_tuple);
  if (blockage_found == false) {
    colour = light -> computelight(
      seer_position, point_on_surface, normal, object);
  }
  return colour;
}

glm::vec4 _compute_reflection(
  glm::vec3 seer_position, glm::vec3 point_on_surface, Primitive* object,
  Scene* scene, int indirect_diffuse_level, int reflection_level,
  int sampling_size, int tid
) {
  glm::vec3 normal = object -> get_normal(point_on_surface);
  glm::vec3 neg_eye_dir = glm::normalize(seer_position - point_on_surface);
  glm::mat3 rot_mat = rotate(180, normal);
  glm::vec3 reflection_dir = rot_mat * neg_eye_dir;
  glm::vec4 colour = glm::vec4(0, 0, 0, 1);
  // unsigned int new_sampling_size = std::max(1, (int)pow(sampling_size, .5));

  Ray reflection_ray = Ray(point_on_surface, reflection_dir);
  std::tuple<bool, glm::vec3, Primitive*> intersection_tuple_ref = \
    scene -> grid -> do_traversal(reflection_ray, INFINITY, false, tid);
  bool intersection_found = std::get<0>(intersection_tuple_ref);
  if (intersection_found) {
    num_ray_intersections++;
    Primitive* nearest_object = std::get<2>(intersection_tuple_ref);
    glm::vec3 point_on_surface_2 = std::get<1>(intersection_tuple_ref);
    glm::vec4 ref_colour;
    ref_colour = _find_colour_pathtracing(
      point_on_surface, point_on_surface_2, nearest_object, scene,
      indirect_diffuse_level - 1, reflection_level - 1, sampling_size, tid);
    colour = glm::vec4(
      ref_colour.x * object -> get_material() -> get_specular().x,
      ref_colour.y * object -> get_material() -> get_specular().y,
      ref_colour.z * object -> get_material() -> get_specular().z,
      ref_colour.w * object -> get_material() -> get_specular().w
    );
  }
  return colour;
}

glm::vec4 _find_colour_pathtracing(
  glm::vec3 seer_position, glm::vec3 point_on_surface, Primitive* object,
  Scene* scene, int indirect_diffuse_level,
  int reflection_level, int sampling_size, int tid
) {

  glm::vec4 colour = object -> get_material() -> get_ambient() + \
    object -> get_material() -> get_emission();
  glm::vec4 direct_lighting = glm::vec4(0, 0, 0, 1);
  glm::vec4 indirect_lighting = glm::vec4(0, 0, 0, 1);

  for (int i = 0; i < scene -> light_array.size(); i++) {
    direct_lighting += _compute_direct_lighting(
      seer_position, point_on_surface, scene -> light_array[i], object,
      scene -> object_array, scene, tid
    );
  }

  if (indirect_diffuse_level > 0) {
    indirect_lighting = _compute_indirect_diffuse(
      point_on_surface, object, scene, indirect_diffuse_level,
      reflection_level, sampling_size, tid
    );
  }

  if (reflection_level > 0 && object -> get_material() -> is_reflective()) {
    colour += _compute_reflection(
      seer_position, point_on_surface, object, scene, indirect_diffuse_level,
      reflection_level, sampling_size, tid);
  }

  glm::vec4 lighting = glm::vec4(
    (direct_lighting.x + indirect_lighting.x) * object ->
    get_material() -> get_albedo().x / M_PI,
    (direct_lighting.y + indirect_lighting.y) * object ->
    get_material() -> get_albedo().y / M_PI,
    (direct_lighting.z + indirect_lighting.z) * object ->
    get_material() -> get_albedo().z / M_PI,
    1
  );

  return colour + lighting;
}

void pathtrace_parallel(
  Scene* scene, int indirect_diffuse_level, int reflection_level,
  int sampling_size
) {

  int i, j;
  int nthreads, tid, chunk = 10;
  std::vector<std::vector<glm::vec4>> image;

  image.resize(scene -> camera -> height);
  for (i = 0; i < scene -> camera -> height; i++) {
    image[floor(i)].resize(scene -> camera -> width);
  }

  #pragma omp parallel shared(image, nthreads, num_primary_rays, scene) private(i, j, tid)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
    printf("Thread %d starting...\n", tid);

    #pragma omp for schedule(dynamic, chunk)
    for (j = 0; j < scene -> camera -> width; j++) {
      for (i = 0; i < scene -> camera -> height; i++) {
        // if (
        //   (i == 127 && j == 333) ||
        //   (i == 159 && j == 360) ||
        //   (i == 119 && j == 71) ||
        //   (i == 190 && j == 391) ||
        //   (i == 172 && j == 309) ||
        //   (i == 181 && j == 271) ||
        //   (i == 159 && j == 359) ||
        //   (i == 127 && j == 332)
        // ) {
          // printf("Processing pixel %d, %d\n", i, j);
          num_primary_rays++;
          Ray camera_ray = scene -> camera -> compute_ray(i + 0.5, j + 0.5);
          // printf("2 (%d, %d)\n", i, j);
          std::tuple<bool, glm::vec3, Primitive*> intersection_tuple = \
            scene -> grid -> do_traversal(camera_ray, INFINITY, false, tid);
          // printf("3 (%d, %d)\n", i, j);
          bool intersection_found = std::get<0>(intersection_tuple);
          if (intersection_found) {
            // printf("4a.1 (%d, %d)\n", i, j);
            Primitive* nearest_object = std::get<2>(intersection_tuple);
            glm::vec3 point_on_surface = std::get<1>(intersection_tuple);
            // printf("4a.2 (%d, %d)\n", i, j);
            image[i][j] = _find_colour_pathtracing(
              scene -> camera -> eye, point_on_surface, nearest_object,
              scene, indirect_diffuse_level, reflection_level, sampling_size,
              tid);
            // printf("4a.3 (%d, %d)\n", i, j);
          } else {
            // printf("4b.1 (%d, %d)\n", i, j);
            image[i][j] = glm::vec4(0, 0, 0, 1);
            // printf("4b.2 (%d, %d)\n", i, j);
          }
          // printf("Finished processing pixel %d, %d\n", i, j);
          pixel_done++;
          if (tid == 0) {
            printf(
              "Progress = %5.5f percent (thread ID: %d).\r",
              100.0 * pixel_done /
                (scene -> camera -> width * scene -> camera -> height),
              tid);
          }
        // }
      }
    }
  }

  save_image(image, scene -> camera -> width, scene -> camera -> height);
}
