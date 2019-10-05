#include "complex_geometry.h"

std::vector<Primitive*> create_rectangle(
  glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3, glm::vec3 point_4,
  glm::vec3 point_1_tex, glm::vec3 point_2_tex, glm::vec3 point_3_tex,
  glm::vec3 point_4_tex, Material* material, glm::mat4 trans_matrix
) {
  std::vector<Primitive*> geom_array;
  std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> \
    parameter_array;

  geom_array.push_back(new Triangle());
  parameter_array = prepare_triangle_parameters(
      point_1, point_2, point_3, point_1_tex, point_2_tex, point_3_tex,
      material, trans_matrix);
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  geom_array.push_back(new Triangle());
  parameter_array = prepare_triangle_parameters(
      point_1, point_3, point_4, point_1_tex, point_3_tex, point_4_tex,
      material, trans_matrix);
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  return geom_array;
}

std::vector<Primitive*> create_rect_pyramid(
  glm::vec3 center_base, double len_base, double width_base, double height,
  Material* material, glm::mat4 trans_matrix
) {
  std::vector<Primitive*> geom_array, additional_geom_array;
  std::vector<std::variant<glm::vec3, double, Material*, glm::mat4>> \
    parameter_array;
  glm::vec3 point_1, point_2, point_3, point_4, point_top;
  double half_len_base = len_base / 2;
  double half_width_base = width_base / 2;

  point_1 = glm::vec3(
    center_base.x - half_len_base, center_base.y + half_width_base, center_base.z);
  point_2 = glm::vec3(
    center_base.x + half_len_base, center_base.y + half_width_base, center_base.z);
  point_3 = glm::vec3(
    center_base.x + half_len_base, center_base.y - half_width_base, center_base.z);
  point_4 = glm::vec3(
    center_base.x - half_len_base, center_base.y - half_width_base, center_base.z);
  point_top = glm::vec3(center_base.x, center_base.y, center_base.z + height);

  // Base
  additional_geom_array = create_rectangle(
    point_1, point_2, point_3, point_4, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  // Faces
  geom_array.push_back(new Triangle());
  parameter_array = prepare_triangle_parameters(
      point_2, point_1, point_top, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
      glm::vec3(1, 0, 0), material, trans_matrix);
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  geom_array.push_back(new Triangle());
  parameter_array = prepare_triangle_parameters(
      point_3, point_2, point_top, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
      glm::vec3(1, 0, 0), material, trans_matrix);
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  geom_array.push_back(new Triangle());
  parameter_array = prepare_triangle_parameters(
      point_4, point_3, point_top, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
      glm::vec3(1, 0, 0), material, trans_matrix);
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  geom_array.push_back(new Triangle());
  parameter_array = prepare_triangle_parameters(
      point_1, point_4, point_top, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
      glm::vec3(1, 0, 0), material, trans_matrix);
  geom_array[geom_array.size() - 1] -> set_parameters(parameter_array);

  return geom_array;
}

std::vector<Primitive*> create_box(
  glm::vec3 center, double len_x, double len_y, double len_z,
  Material* material, glm::mat4 trans_matrix
) {
  std::vector<Primitive*> geom_array, additional_geom_array;
  double half_len_x = len_x / 2;
  double half_len_y = len_y / 2;
  double half_len_z = len_z / 2;

  // Front
  additional_geom_array = create_rectangle(
    glm::vec3(center.x - half_len_x, center.y + half_len_y, center.z - half_len_z),
    glm::vec3(center.x + half_len_x, center.y + half_len_y, center.z - half_len_z),
    glm::vec3(center.x + half_len_x, center.y - half_len_y, center.z - half_len_z),
    glm::vec3(center.x - half_len_x, center.y - half_len_y, center.z - half_len_z),
    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  // Back
  additional_geom_array = create_rectangle(
    glm::vec3(center.x + half_len_x, center.y + half_len_y, center.z + half_len_z),
    glm::vec3(center.x - half_len_x, center.y + half_len_y, center.z + half_len_z),
    glm::vec3(center.x - half_len_x, center.y - half_len_y, center.z + half_len_z),
    glm::vec3(center.x + half_len_x, center.y - half_len_y, center.z + half_len_z),
    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  // Bottom
  additional_geom_array = create_rectangle(
    glm::vec3(center.x + half_len_x, center.y - half_len_y, center.z + half_len_z),
    glm::vec3(center.x - half_len_x, center.y - half_len_y, center.z + half_len_z),
    glm::vec3(center.x - half_len_x, center.y - half_len_y, center.z - half_len_z),
    glm::vec3(center.x + half_len_x, center.y - half_len_y, center.z - half_len_z),
    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  // Top
  additional_geom_array = create_rectangle(
    glm::vec3(center.x - half_len_x, center.y + half_len_y, center.z - half_len_z),
    glm::vec3(center.x - half_len_x, center.y + half_len_y, center.z + half_len_z),
    glm::vec3(center.x + half_len_x, center.y + half_len_y, center.z + half_len_z),
    glm::vec3(center.x + half_len_x, center.y + half_len_y, center.z - half_len_z),
    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  // Left
  additional_geom_array = create_rectangle(
    glm::vec3(center.x - half_len_x, center.y + half_len_y, center.z + half_len_z),
    glm::vec3(center.x - half_len_x, center.y + half_len_y, center.z - half_len_z),
    glm::vec3(center.x - half_len_x, center.y - half_len_y, center.z - half_len_z),
    glm::vec3(center.x - half_len_x, center.y - half_len_y, center.z + half_len_z),
    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  // Right
  additional_geom_array = create_rectangle(
    glm::vec3(center.x + half_len_x, center.y + half_len_y, center.z + half_len_z),
    glm::vec3(center.x + half_len_x, center.y - half_len_y, center.z + half_len_z),
    glm::vec3(center.x + half_len_x, center.y - half_len_y, center.z - half_len_z),
    glm::vec3(center.x + half_len_x, center.y + half_len_y, center.z - half_len_z),
    glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0), material, trans_matrix
  );
  add_to_geom_array(geom_array, additional_geom_array);

  return geom_array;
}
